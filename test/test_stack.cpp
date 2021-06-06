/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:17:25 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 15:40:16 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void test_stack(void)
{
	std::cout << "     <<< Stack test start >>>" << std::endl;

	// (constructor)
	std::cout << "----- constructor test -----" << std::endl;
	{
		LIST<int> mylist(3, 100);   // list with 3 elements
		VECTOR<int> myvector(2, 200); // vector with 2 elements

		STACK<int, LIST<int> > first;			 // empty stack
		STACK<int, LIST<int> > second(mylist); // stack initialized to copy of list

		STACK<int, VECTOR<int> > third; // empty stack using vector
		STACK<int, VECTOR<int> > fourth(myvector);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
		std::cout << "size of fourth: " << fourth.size() << '\n';
	}

	// empty
	std::cout << "\n----- empty -----" << std::endl;
	{
		STACK<int> mystack;
		int sum(0);

		for (int i = 1; i <= 10; i++)
			mystack.push(i);

		while (!mystack.empty())
		{
			sum += mystack.top();
			mystack.pop();
		}

		std::cout << "total: " << sum << '\n';
	}

	// size
	std::cout << "\n----- size -----" << std::endl;
	{
		STACK<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i = 0; i < 5; i++)
			myints.push(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.pop();
		std::cout << "2. size: " << myints.size() << '\n';
	}

	// top
	std::cout << "\n----- top -----" << std::endl;
	{
		STACK<int> mystack;

		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;

		std::cout << "mystack.top() is now " << mystack.top() << '\n';
	}

	// push,pop
	std::cout << "\n----- push/pop -----" << std::endl;
	{
		STACK<int> mystack;

		for (int i = 0; i < 5; ++i)
			mystack.push(i);

		std::cout << "Popping out elements...";
		while (!mystack.empty())
		{
			std::cout << ' ' << mystack.top();
			mystack.pop();
		}
		std::cout << '\n';
	}

	std::cout << "     <<< Stack test end >>>" << std::endl;
}
