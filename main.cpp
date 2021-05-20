#include <iostream>
#include <list>
#include "list.hpp"

int main()
{
	ft::list<int> mylist;

	for (int i = 1; i <= 5; ++i)
		mylist.push_back(i);

	std::cout << "mylist backwards:";
	for (ft::list<int>::reverse_iterator rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
	{
		std::cout << ' ' << *rit;
	}
	std::cout << '\n';


	
	mylist.erase(mylist.begin());
	mylist.erase(mylist.begin());
	//mylist.erase(mylist.end());

	mylist.erase(mylist.begin(), mylist.end());

	std::cout << "mylist backwards:";
	for (ft::list<int>::reverse_iterator rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
	{
		std::cout << ' ' << *rit;
	}
	std::cout << '\n';


	std::list<int> og_list;

	for (int i = 1; i <= 5; i++){
		og_list.push_back(i);
	}

	//og_list.erase(og_list.end());

	for (std::list<int>::iterator it = og_list.begin(); it != og_list.end(); it++){
		std::cout << *it << " " ;
	}
	std::cout << std::endl;

	return 0;
}