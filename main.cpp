// constructing maps
#include <iostream>
#include <utility>
#include "map.hpp"

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{
		return lhs < rhs;
	}
};

void print(ft::map<char, int> &map)
{
	for (ft::map<char, int>::iterator it = map.begin(); it != map.end(); it++){
		std::cout << (*it).first << " " << (*it).second << std::endl;
	}
	std::cout << "--------------------------" << std::endl;
}

int main()
{
	ft::map<char, int> first;

	/*
  	first['a']=10;
  	first['b']=30;
  	first['c']=50;
  	first['d']=70;
  	*/
	first.insert(std::pair<char, int>('a', 10));
	first.insert(std::pair<char, int>('b', 30));
	first.insert(std::pair<char, int>('c', 50));
	first.insert(std::pair<char, int>('d', 70));

	print(first);

	ft::map<char, int> second(first.begin(), first.end());

	print(second);

	ft::map<char, int> third(second);

	print(third);

	ft::map<char, int, classcomp> fourth; // class as Compare

	bool (*fn_pt)(char, char) = fncomp;
	ft::map<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare

	return 0;
}
