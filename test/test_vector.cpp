/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 02:03:57 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 21:56:32 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void test_vector(void)
{
	std::cout << "     <<< Vector test start >>>" << std::endl;

	// (constructor)
	std::cout << "----- constructor -----" << std::endl;
	{
		// constructors used in the same order as described above:
		VECTOR<int> first;									// empty vector of ints
		VECTOR<int> second(4, 100);							// four ints with value 100
		VECTOR<int> third(second.begin(), second.end());	// iterating through second
		VECTOR<int> fourth(third);							// a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16, 2, 77, 29};
		VECTOR<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

		std::cout << "The contents of fifth are:";
		for (VECTOR<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// operator=
	std::cout << "\n----- operator= -----" << std::endl;
	{
		VECTOR<int> foo(3, 0);
		VECTOR<int> bar(5, 0);

		bar = foo;
		foo = VECTOR<int>();

		std::cout << "Size of foo: " << int(foo.size()) << '\n';
		std::cout << "Size of bar: " << int(bar.size()) << '\n';
	}

	// begin
	std::cout << "\n----- begin -----" << std::endl;
	{
		VECTOR<int> myvector;
		for (int i = 1; i <= 5; i++)
			myvector.push_back(i);

		std::cout << "myvector contains:";
		for (VECTOR<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// end
	std::cout << "\n----- end -----" << std::endl;
	{
		VECTOR<int> myvector;
		for (int i = 1; i <= 5; i++)
			myvector.push_back(i);

		std::cout << "myvector contains:";
		for (VECTOR<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// rbegin
	std::cout << "\n----- rbegin -----" << std::endl;
	{
		VECTOR<int> myvector(5); // 5 default-constructed ints

		int i = 0;

		VECTOR<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit != myvector.rend(); ++rit)
			*rit = ++i;

		std::cout << "myvector contains:";
		for (VECTOR<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// rend
	std::cout << "\n----- rend -----" << std::endl;
	{
		VECTOR<int> myvector(5); // 5 default-constructed ints

		VECTOR<int>::reverse_iterator rit = myvector.rbegin();

		int i = 0;
		for (rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
			*rit = ++i;

		std::cout << "myvector contains:";
		for (VECTOR<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// size
	std::cout << "\n-----  -----" << std::endl;
	{
		VECTOR<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i = 0; i < 10; i++)
			myints.push_back(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.insert(myints.end(), 10, 100);
		std::cout << "2. size: " << myints.size() << '\n';

		myints.pop_back();
		std::cout << "3. size: " << myints.size() << '\n';
	}

	// max_size
	std::cout << "\n----- max_size -----" << std::endl;
	{
		VECTOR<int> myvector;

		// set some content in the vector:
		for (int i = 0; i < 100; i++)
			myvector.push_back(i);

		std::cout << "size: " << myvector.size() << "\n";
		std::cout << "capacity: " << myvector.capacity() << "\n";
		std::cout << "max_size: " << myvector.max_size() << "\n";
	}

	// resize
	std::cout << "\n----- resize -----" << std::endl;
	{
		VECTOR<int> myvector;

		// set some initial content:
		for (int i = 1; i < 10; i++)
			myvector.push_back(i);

		myvector.resize(5);
		myvector.resize(8, 100);
		myvector.resize(12);

		std::cout << "myvector contains:";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}

	// capacity
	std::cout << "\n----- capacity -----" << std::endl;
	{
		VECTOR<int> myvector;

		// set some content in the vector:
		for (int i = 0; i < 100; i++)
			myvector.push_back(i);

		std::cout << "size: " << (int)myvector.size() << '\n';
		std::cout << "capacity: " << (int)myvector.capacity() << '\n';
		std::cout << "max_size: " << (int)myvector.max_size() << '\n';
	}

	// empty
	std::cout << "\n----- empty -----" << std::endl;
	{
		VECTOR<int> myvector;
		int sum(0);

		for (int i = 1; i <= 10; i++)
			myvector.push_back(i);

		while (!myvector.empty())
		{
			sum += myvector.back();
			myvector.pop_back();
		}

		std::cout << "total: " << sum << '\n';
	}

	// reserve
	std::cout << "\n----- reserve -----" << std::endl;
	{
		VECTOR<int>::size_type sz;

		VECTOR<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			foo.push_back(i);
			if (sz != foo.capacity())
			{
				sz = foo.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}

		VECTOR<int> bar;
		sz = bar.capacity();
		bar.reserve(100); // this is the only difference with foo above
		std::cout << "making bar grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			bar.push_back(i);
			if (sz != bar.capacity())
			{
				sz = bar.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}
	}

	// operator[]
	std::cout << "\n----- operator[] -----" << std::endl;
	{
		VECTOR<int> myvector(10); // 10 zero-initialized elements

		VECTOR<int>::size_type sz = myvector.size();

		// assign some values:
		for (unsigned i = 0; i < sz; i++)
			myvector[i] = i;

		// reverse vector using operator[]:
		for (unsigned i = 0; i < sz / 2; i++)
		{
			int temp;
			temp = myvector[sz - 1 - i];
			myvector[sz - 1 - i] = myvector[i];
			myvector[i] = temp;
		}

		std::cout << "myvector contains:";
		for (unsigned i = 0; i < sz; i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}

	// at
	std::cout << "\n----- at -----" << std::endl;
	{
		VECTOR<int> myvector(10); // 10 zero-initialized ints

		// assign some values:
		for (unsigned i = 0; i < myvector.size(); i++)
			myvector.at(i) = i;

		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector.at(i);
		std::cout << '\n';
	}

	// front
	std::cout << "\n----- front -----" << std::endl;
	{
		VECTOR<int> myvector;

		myvector.push_back(78);
		myvector.push_back(16);

		// now front equals 78, and back 16

		myvector.front() -= myvector.back();

		std::cout << "myvector.front() is now " << myvector.front() << '\n';
	}

	// back
	std::cout << "\n----- back -----" << std::endl;
	{
		VECTOR<int> myvector;

		myvector.push_back(10);

		while (myvector.back() != 0)
		{
			myvector.push_back(myvector.back() - 1);
		}

		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}

	// assign
	std::cout << "\n----- assign -----" << std::endl;
	{
		VECTOR<int> first;
		VECTOR<int> second;
		VECTOR<int> third;

		first.assign(7, 100); // 7 ints with a value of 100

		VECTOR<int>::iterator it;
		it = first.begin() + 1;

		second.assign(it, first.end() - 1); // the 5 central values of first

		int myints[] = {1776, 7, 4};
		third.assign(myints, myints + 3); // assigning from array.

		std::cout << "Size of first: " << int(first.size()) << '\n';
		std::cout << "Size of second: " << int(second.size()) << '\n';
		std::cout << "Size of third: " << int(third.size()) << '\n';
	}

	// push_back
	std::cout << "\n----- push_back -----" << std::endl;
	{
		VECTOR<int> myvector;
		int myint;

		std::cout << "Please enter some integers (enter 0 to end):\n";

		do
		{
			std::cin >> myint;
			myvector.push_back(myint);
		} while (myint);

		std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
	}

	// pop_back
	std::cout << "\n----- pop_back -----" << std::endl;
	{
		VECTOR<int> myvector;
		int myint;

		std::cout << "Please enter some integers (enter 0 to end):\n";

		do
		{
			std::cin >> myint;
			myvector.push_back(myint);
		} while (myint);

		std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
	}

	// insert
	std::cout << "\n----- insert -----" << std::endl;
	{
		VECTOR<int> myvector(3, 100);
		VECTOR<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert(it, 200);

		myvector.insert(it, 2, 300);

		// "it" no longer valid, get a new one:
		it = myvector.begin();

		VECTOR<int> anothervector(2, 400);
		myvector.insert(it + 2, anothervector.begin(), anothervector.end());

		int myarray[] = {501, 502, 503};
		myvector.insert(myvector.begin(), myarray, myarray + 3);

		std::cout << "myvector contains:";
		for (it = myvector.begin(); it < myvector.end(); it++)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// erase
	std::cout << "\n----- erase -----" << std::endl;
	{
		VECTOR<int> myvector;

		// set some values (from 1 to 10)
		for (int i = 1; i <= 10; i++)
			myvector.push_back(i);

		// erase the 6th element
		myvector.erase(myvector.begin() + 5);

		// erase the first 3 elements:
		myvector.erase(myvector.begin(), myvector.begin() + 3);

		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector.size(); ++i)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}

	// swap
	std::cout << "\n----- swap -----" << std::endl;
	{
		VECTOR<int> foo(3, 100); // three ints with a value of 100
		VECTOR<int> bar(5, 200); // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo contains:";
		for (unsigned i = 0; i < foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << '\n';

		std::cout << "bar contains:";
		for (unsigned i = 0; i < bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << '\n';
	}	

	// clear
	std::cout << "\n----- clear -----" << std::endl;
	{
		VECTOR<int> myvector;
		myvector.push_back(100);
		myvector.push_back(200);
		myvector.push_back(300);

		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';

		myvector.clear();
		myvector.push_back(1101);
		myvector.push_back(2202);

		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}

	// relational operators
	std::cout << "\n----- relational operators -----" << std::endl;
	{
		VECTOR<int> foo(3, 100); // three ints with a value of 100
		VECTOR<int> bar(2, 200); // two ints with a value of 200

		if (foo == bar)
			std::cout << "foo and bar are equal\n";
		if (foo != bar)
			std::cout << "foo and bar are not equal\n";
		if (foo < bar)
			std::cout << "foo is less than bar\n";
		if (foo > bar)
			std::cout << "foo is greater than bar\n";
		if (foo <= bar)
			std::cout << "foo is less than or equal to bar\n";
		if (foo >= bar)
			std::cout << "foo is greater than or equal to bar\n";
	}

	// swap (non-member)
	std::cout << "\n----- swap (non-member) -----" << std::endl;
	{
		VECTOR<int> foo(3, 100); // three ints with a value of 100
		VECTOR<int> bar(5, 200); // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo contains:";
		for (VECTOR<int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "bar contains:";
		for (VECTOR<int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

    std::cout << "     <<< Vector test end >>>" << std::endl;
}
