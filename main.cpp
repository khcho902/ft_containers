
#include <iostream>
#include "list.hpp"

int main(void)
{
	ft::list<int> lst;

	lst.push_back(10);
	lst.push_back(10000);
	lst.push_back(10);
	lst.push_back(10);
	lst.push_back(10);

	ft::list<int>::_Node* tmp = static_cast<ft::list<int>::_Node*>(lst.sentry_node.next);

	while (tmp != &lst.sentry_node)
	{
		std::cout << tmp->data << std::endl;
		tmp = static_cast<ft::list<int>::_Node*>(tmp->next);
	}

	return (0);
}