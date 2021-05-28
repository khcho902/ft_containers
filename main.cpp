#include <iostream>
#include "utils.hpp"
#include "rb_tree.hpp"

int main()
{
	typedef char					key_type;
	typedef std::pair<char, int>	value_type;
	typedef std::less<char>			key_compare;
	
	typedef std::allocator<std::pair<const char, int> >::rebind<value_type>::other  _Pair_alloc_type;

	typedef ft::rb_tree<key_type, value_type, ft::Select1st<value_type>, key_compare, _Pair_alloc_type>  Rb_tree;

	Rb_tree tree;

	// first insert function version (single parameter):
	tree.insert_unique(std::pair<char, int>('a', 100));
	tree.insert_unique(std::pair<char, int>('z', 200));

	std::pair<Rb_tree::iterator, bool> ret;
	ret = tree.insert_unique(std::pair<char, int>('z', 500));
	if (ret.second == false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	Rb_tree::iterator it = tree.begin();
	tree.insert_unique_(it, std::pair<char, int>('b', 300)); // max efficiency inserting
	tree.insert_unique_(it, std::pair<char, int>('c', 400)); // no max efficiency inserting

	// third insert function version (range insertion):
	Rb_tree::iterator it2 = tree.begin();
	it2++;
	it2++;
	Rb_tree anothertree;
	anothertree.insert_unique(tree.begin(), it2);

	// showing contents:
	std::cout << "tree contains:\n";
	for (it = tree.begin(); it != tree.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it = anothertree.begin(); it != anothertree.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	return 0;
}
