// erasing from map
#include <iostream>
#include "map.hpp"

int main()
{
	ft::map<char, int> mymap;

	mymap.insert(std::pair<char, int>('x', 100));
	mymap.insert(std::pair<char, int>('y', 200));
	mymap.insert(std::pair<char, int>('z', 300));

	std::cout << "mymap contains:\n";
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mymap.clear();

	mymap.insert(std::pair<char, int>('a', 11001));
	mymap.insert(std::pair<char, int>('b', 22002));


	std::cout << "mymap contains:\n";
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	return 0;
}
