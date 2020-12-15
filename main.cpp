#include "Route.h"

std::ostream& operator<<(std::ostream& out, const vector<string> v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<string>(out, " "));
	return out;
}
std::ostream& operator<<(std::ostream& out, const std::pair<size_t, Route> &p)
{
	out << "first: " << p.first << " second: " << p.second;
	return out;
}
std::ostream& operator<<(std::ostream& out, const std::pair<size_t, string>& p)
{
	out << p.first << " " << p.second;
	return out;
}

int main()
{
	setlocale(0, "");
	read_data("text.txt");
	//std::copy(busRoutes.begin(), busRoutes.end(), std::ostream_iterator<vector<string>>(cout, "\n"));

	for (size_t i = 0; i < busRoutes.size(); i++)
	{
		cout << busRoutes[i] << "\n";
	}

	vector<Route> temp = collect_v(busRoutes);
	std::multimap<size_t, Route> mm = create_map_by_bus(temp);
	std::copy(mm.begin(), mm.end(), std::ostream_iterator<std::pair<size_t, Route>>(cout, "\n"));

	set<std::pair<size_t, string>> tempset = buses_list(temp);
	//--------------------RUNTIME ERROR-------------------------
	//std::copy(tempset.begin(), tempset.end(), std::ostream_iterator<std::pair<size_t, string>>(cout, "\n"));
	set<string> drivers = same_bus_drivers_list(temp, "Маз");
	std::copy(drivers.begin(), drivers.end(), std::ostream_iterator<string>(cout, "\n"));
	

	/*vector<Route> vr;
	vr = collect(busRoutes);
	std::copy(vr.begin(), vr.end(), std::ostream_iterator<Route>(cout, "\n"));

	auto temp = create_map(vr);
	std::copy(temp.begin(), temp.end(), std::ostream_iterator<std::pair<size_t, Route>>(cout, "\n"));*/

	return 0;
}