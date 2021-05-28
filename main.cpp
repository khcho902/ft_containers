// swap lists
#include <iostream>
#include "list.hpp"
#include "rb_tree.hpp"

int main()
{
	/*
	ft::list<int> first(3, 100);  // three ints with a value of 100
	ft::list<int> second(5, 200); // five ints with a value of 200

	first.swap(second);

	std::cout << "first contains:";
	for (ft::list<int>::iterator it = first.begin(); it != first.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (ft::list<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
	*/

	/*
	std::map<char, int> mymap;

	// first insert function version (single parameter):
	mymap.insert(std::pair<char, int>('a', 100));
	mymap.insert(std::pair<char, int>('z', 200));
	*/

	typedef char					key_type;
	typedef std::pair<char, int>	value_type;
	typedef std::less<char>			key_compare;
	
	typedef std::allocator<std::pair<const char, int> >::rebind<value_type>::other  _Pair_alloc_type;

	typedef ft::rb_tree<key_type, value_type, ft::Select1st<value_type>, key_compare, _Pair_alloc_type>  Rb_tree;

	Rb_tree tree;

	tree.insert_unique(std::pair<char, int>('b', 200));
	tree.insert_unique(std::pair<char, int>('d', 400));
	tree.insert_unique(std::pair<char, int>('a', 100));
	tree.insert_unique(std::pair<char, int>('c', 300));

	Rb_tree::iterator it = tree.begin();

	while (it != tree.end())
	{
		std::cout << (*it).first << std::endl;
		std::cout << (*it).second << std::endl;
		it++;

	}

	return 0;
}
