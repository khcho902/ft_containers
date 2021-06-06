/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 16:24:27 by kycho             #+#    #+#             */
/*   Updated: 2021/06/07 00:33:03 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void test_queue(void)
{
	std::cout << "     <<< Queue test start >>>" << std::endl;

	// (constructor)
	std::cout << "----- constructor -----" << std::endl;
	{
		LIST<int> mylist(2, 200);	// list with 2 elements

		QUEUE<int> first;			// empty queue

		QUEUE<int, LIST<int> > second; // empty queue with list as underlying container
		QUEUE<int, LIST<int> > third(mylist);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
	}

	// empty
	std::cout << "\n----- empty -----" << std::endl;
	{
		QUEUE<int> myqueue;
		int sum(0);

		for (int i = 1; i <= 10; i++)
			myqueue.push(i);

		while (!myqueue.empty())
		{
			sum += myqueue.front();
			myqueue.pop();
		}

		std::cout << "total: " << sum << '\n';
	}

	// size
	std::cout << "\n----- size -----" << std::endl;
	{
		QUEUE<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i = 0; i < 5; i++)
			myints.push(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.pop();
		std::cout << "2. size: " << myints.size() << '\n';
	}

	// front
	std::cout << "\n----- front -----" << std::endl;
	{
		QUEUE<int> myqueue;

		myqueue.push(77);
		myqueue.push(16);

		myqueue.front() -= myqueue.back(); // 77-16=61

		std::cout << "myqueue.front() is now " << myqueue.front() << '\n';
	}

	// back
	std::cout << "\n----- back -----" << std::endl;
	{
		QUEUE<int> myqueue;

		myqueue.push(12);
		myqueue.push(75); // this is now the back

		myqueue.back() -= myqueue.front();

		std::cout << "myqueue.back() is now " << myqueue.back() << '\n';
	}

	// push,pop
	std::cout << "\n----- push/pop -----" << std::endl;
	{
		QUEUE<int> myqueue;

		/*
		int myint;
		std::cout << "Please enter some integers (enter 0 to end):\n";

		do
		{
			std::cin >> myint;
			myqueue.push(myint);
		} while (myint);
		*/

		myqueue.push(1);
		myqueue.push(2);
		myqueue.push(3);
		myqueue.push(4);
		myqueue.push(5);
		myqueue.push(6);
		myqueue.push(7);
		myqueue.push(8);
		myqueue.push(9);
		myqueue.push(10);

		std::cout << "myqueue contains: ";
		while (!myqueue.empty())
		{
			std::cout << ' ' << myqueue.front();
			myqueue.pop();
		}
		std::cout << '\n';
	}
}
