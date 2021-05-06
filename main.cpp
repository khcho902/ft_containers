
#include <iostream>
#include "list.hpp"

int main(void)
{
	ft::list<int> lst;

	lst.push_back(10);
	lst.push_back(20000);
	lst.push_back(30);
	lst.push_back(40);
	lst.push_back(50);

	for(ft::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		std::cout << (*it)++ << std::endl;
	}

	for(ft::list<int>::const_iterator it = lst.begin(); it != lst.end(); it++)
	{
		std::cout << (*it) << std::endl;
	}

	return (0);
}