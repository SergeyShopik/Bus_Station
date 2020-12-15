#pragma once
#include<iostream>
using std::cout;
using std::cin;
#include<fstream>
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<sstream>
#include<iterator>
#include<algorithm>
#include<map>
#include<set>
using std::set;
#include<list>
using std::list;
#include<queue>
using std::deque;

class Route
{
public:
	Route() {};
	Route(std::pair<size_t, string> bus_, string driver_, size_t routeNum_) :
		bus(bus_), driver(driver_), routeNum(routeNum_) {}
	~Route() {};

	std::pair<size_t, string> get_bus() const { return bus; }
	size_t get_routeNum() const { return routeNum; }
	string get_driver() const { return driver; }

	Route& operator=(const string& s) 
	{ 
		driver = s;
		return *this; 
	}

	//transform buses in vector/list/deque
	friend vector<Route> collect_v(vector<vector<string>> buses);
	friend list<Route> collect_l(vector<vector<string>> buses);
	friend deque<Route> collect_d(vector<vector<string>> buses);


	friend std::ostream& operator<<(std::ostream& out, const Route&);

private:
	std::pair<size_t, string> bus;
	string driver;
	size_t routeNum;
};

vector<vector<string>> busRoutes;
//----------------------------------------------------------------------------------------------------
void read_data(string filename)
{
	std::ifstream in(filename);
	string str;
	while (std::getline(in, str))
	{
		std::istringstream ss(str);

		vector<string> temp;
		while (ss >> str)
			temp.push_back(str);//inner vector

		busRoutes.push_back(temp);//outer vector
	}
}
//----------------------------------------------------------------------------------------------------
vector<Route> collect_v(vector<vector<string>> buses)
{
	vector<Route> result(buses.size());
	std::transform(buses.begin(), buses.end(), result.begin(), [](vector<string> obj)
		{
			return Route(std::make_pair(std::stoi(obj[2]), obj[3]), obj[1], std::stoi(obj[0]));
		});
	return result;
}
list<Route> collect_l(vector<vector<string>> buses)
{
	list<Route> result(buses.size());
	std::transform(buses.begin(), buses.end(), result.begin(), [](vector<string> obj)
		{
			return Route(std::make_pair(std::stoi(obj[2]), obj[3]), obj[1], std::stoi(obj[0]));
		});
	return result;
}
deque<Route> collect_d(vector<vector<string>> buses)
{
	deque<Route> result(buses.size());
	std::transform(buses.begin(), buses.end(), result.begin(), [](vector<string> obj)
		{
			return Route(std::make_pair(std::stoi(obj[2]), obj[3]), obj[1], std::stoi(obj[0]));
		});
	return result;
}
//----------------------------------------------------------------------------------------------------
void sort_busnum(vector<Route>& v)
{
	std::sort(v.begin(), v.end(), [](const Route& obj1, const Route& obj2)
		{
			return obj1.get_bus().first > obj2.get_bus().first;
		});
}
void sort_route(vector<Route>& v)
{
	std::sort(v.begin(), v.end(), [](const Route& obj1, const Route& obj2)
		{
			return obj1.get_routeNum() > obj2.get_routeNum();
		});
}
void sort_driver(vector<Route>& v)
{
	std::sort(v.begin(), v.end(), [](const Route& obj1, const Route& obj2)
		{
			return obj1.get_driver() > obj2.get_driver();
		});
}
//----------------------------------------------------------------------------------------------------
std::multimap<size_t, Route> create_map_by_route(vector<Route>& v)
{
	std::multimap<size_t, Route> result;
	std::transform(v.begin(), v.end(), std::inserter(result, result.begin()), [](Route& obj) 
		{
			return std::make_pair(obj.get_routeNum(), obj);
		});
	return result;
}
std::multimap<size_t, Route> create_map_by_bus(vector<Route>& v)
{
	std::multimap<size_t, Route> result;
	std::transform(v.begin(), v.end(), std::inserter(result, result.begin()), [](Route& obj)
		{
			return std::make_pair(obj.get_bus().first, obj);
		});
	return result;
}
//----------------------------------------------------------------------------------------------------
set<size_t> routes_list(vector<Route>& v)
{
	set<size_t> result;
	std::transform(v.begin(), v.end(), std::inserter(result, result.begin()), [](Route& obj)
		{
			return obj.get_routeNum();
		});
	return result;
}
set<std::pair<size_t, string>> buses_list(vector<Route>& v)
{
	set<std::pair<size_t, string>> result;
	std::transform(v.begin(), v.end(), std::inserter(result, result.begin()), [](Route& obj)
		{
			return obj.get_bus();
		});
	return result;
}
//-----------------------------LANBDA------------------------------
//set<string> same_bus_drivers_list(vector<Route>& v, string bus)
//{
//	set<string> result;
//	std::transform(v.begin(), v.end(), std::inserter(result, result.begin()), [bus](Route& obj)
//		{
//			if (obj.get_bus().second == bus) return obj.get_driver();
//			return;
//		});
//	return result;
//}
//----------------------------------------------------------------------------------------------------
void delete_by_route(std::multimap<size_t, Route>& c, const int num)
{
	c.erase(num);
}
void replace_driver_on_rout(vector<Route> v, size_t routeNum, string driver, const string& newDriver)
{
	std::replace_if(v.begin(), v.end(), [routeNum, driver](Route& obj)
		{
			if (obj.get_routeNum() == routeNum && obj.get_driver() == driver)
			return true;
		}, newDriver);
}
//size_t max_buses_on_route(vector<Route> v)
//{
//	std::multimap<size_t, size_t> result;
//	std::sort(v.begin(), v.end(), [](Route& obj1, Route& obj2)
//		{
//			return obj1.get_routeNum() <= obj2.get_routeNum();
//		});
//
//	size_t countBuses = 0, routeNum;
//	std::transform(v.begin(), v.end(), std::inserter(result, result.begin()), [&countBuses, &routeNum](Route& obj)
//		{
//			routeNum = obj.get_routeNum();
//			if (routeNum == )
//		});
//}

std::ostream& operator<<(std::ostream& out, const Route& r)
{
	out << "Bus: " << r.bus.first << " " << r.bus.second << " Driver: " << r.driver << " Num of route: " << r.routeNum << "\n";
	return out;
}
