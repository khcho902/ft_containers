// swap lists
#include <iostream>
#include "list.hpp"
#include "rb_tree.hpp"

int main()
{
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

	return 0;
}
