/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_multiset.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 21:53:32 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 22:11:58 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

bool multiset_fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const int &lhs, const int &rhs) const
	{
		return lhs < rhs;
	}
};

void test_multiset(void)
{
	std::cout << "     <<< Multiset test start >>>" << std::endl;

	// (constructor)
	std::cout << "----- constructor -----" << std::endl;
	{
		MULTISET<int> first; // empty multiset of ints

		int myints[] = {10, 20, 30, 20, 20};
		MULTISET<int> second(myints, myints + 5); // pointers used as iterators

		MULTISET<int> third(second); // a copy of second

		MULTISET<int> fourth(second.begin(), second.end()); // iterator ctor.

		MULTISET<int, classcomp> fifth; // class as Compare

		bool (*fn_pt)(int, int) = multiset_fncomp;
		MULTISET<int, bool (*)(int, int)> sixth(fn_pt); // function pointer as Compare
	}

	// operator=
	std::cout << "\n----- operator= -----" << std::endl;
	{
		int myints[] = {19, 81, 36, 36, 19};
		MULTISET<int> first(myints, myints + 5); // multiset with 5 ints
		MULTISET<int> second;					  // empty multiset

		second = first;				  // now second contains the 5 ints
		first = MULTISET<int>(); // and first is empty

		std::cout << "Size of first: " << first.size() << '\n';
		std::cout << "Size of second: " << second.size() << '\n';
	}

	// begin
	std::cout << "\n----- begin -----" << std::endl;
	{
		int myints[] = {42, 71, 71, 71, 12};
		MULTISET<int> mymultiset(myints, myints + 5);

		MULTISET<int>::iterator it;

		std::cout << "mymultiset contains:";
		for (MULTISET<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;

		std::cout << '\n';
	}

	// end
	std::cout << "\n----- end -----" << std::endl;
	{
		int myints[] = {15, 98, 77, 77, 39};
		MULTISET<int> mymultiset(myints, myints + 5);

		std::cout << "mymultiset contains:";
		for (MULTISET<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;

		std::cout << '\n';
	}

	// rbegin, rend
	std::cout << "\n----- rbegin/rend -----" << std::endl;
	{
		int myints[] = {77, 16, 2, 30, 30};
		MULTISET<int> mymultiset(myints, myints + 5);

		std::cout << "mymultiset contains:";
		for (MULTISET<int>::reverse_iterator rit = mymultiset.rbegin(); rit != mymultiset.rend(); ++rit)
			std::cout << ' ' << *rit;

		std::cout << '\n';
	}

	// empty
	std::cout << "\n----- empty -----" << std::endl;
	{
		MULTISET<int> mymultiset;

		mymultiset.insert(10);
		mymultiset.insert(20);
		mymultiset.insert(10);

		std::cout << "mymultiset contains:";
		while (!mymultiset.empty())
		{
			std::cout << ' ' << *mymultiset.begin();
			mymultiset.erase(mymultiset.begin());
		}
		std::cout << '\n';
	}

	// size
	std::cout << "\n----- size -----" << std::endl;
	{
		MULTISET<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i = 0; i < 10; i++)
			myints.insert(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.insert(5);
		std::cout << "2. size: " << myints.size() << '\n';

		myints.erase(5);
		std::cout << "3. size: " << myints.size() << '\n';
	}

	// max_size
	std::cout << "\n----- max_size -----" << std::endl;
	{
		MULTISET<int> mymultiset;

		if (mymultiset.max_size() > 1000)
		{
			for (int i = 0; i < 1000; i++)
				mymultiset.insert(i);
			std::cout << "The multiset contains 1000 elements.\n";
		}
		else
			std::cout << "The multiset could not hold 1000 elements.\n";
	}

	// insert
	std::cout << "\n----- insert -----" << std::endl;
	{
		MULTISET<int> mymultiset;
		MULTISET<int>::iterator it;

		// set some initial values:
		for (int i = 1; i <= 5; i++)
			mymultiset.insert(i * 10); // 10 20 30 40 50

		it = mymultiset.insert(25);

		it = mymultiset.insert(it, 27); // max efficiency inserting
		it = mymultiset.insert(it, 29); // max efficiency inserting
		it = mymultiset.insert(it, 24); // no max efficiency inserting (24<29)

		int myints[] = {5, 10, 15};
		mymultiset.insert(myints, myints + 3);

		std::cout << "mymultiset contains:";
		for (it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// erase
	std::cout << "\n----- erase -----" << std::endl;
	{
		MULTISET<int> mymultiset;
		MULTISET<int>::iterator it;

		// insert some values:
		mymultiset.insert(40); // 40
		for (int i = 1; i < 7; i++)
			mymultiset.insert(i * 10); // 10 20 30 40 40 50 60

		it = mymultiset.begin();
		it++; //    ^

		mymultiset.erase(it); // 10 30 40 40 50 60

		mymultiset.erase(40); // 10 30 50 60

		it = mymultiset.find(50);
		mymultiset.erase(it, mymultiset.end()); // 10 30

		std::cout << "mymultiset contains:";
		for (it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// swap
	std::cout << "\n----- swap -----" << std::endl;
	{
		int myints[] = {19, 72, 4, 36, 20, 20};
		MULTISET<int> first(myints, myints + 3);	   // 4,19,72
		MULTISET<int> second(myints + 3, myints + 6); // 20,20,36

		first.swap(second);

		std::cout << "first contains:";
		for (MULTISET<int>::iterator it = first.begin(); it != first.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "second contains:";
		for (MULTISET<int>::iterator it = second.begin(); it != second.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// clear
	std::cout << "\n----- clear -----" << std::endl;
	{
		MULTISET<int> mymultiset;

		mymultiset.insert(11);
		mymultiset.insert(42);
		mymultiset.insert(11);

		std::cout << "mymultiset contains:";
		for (MULTISET<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		mymultiset.clear();
		mymultiset.insert(200);
		mymultiset.insert(100);

		std::cout << "mymultiset contains:";
		for (MULTISET<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;

		std::cout << '\n';
	}

	// key_comp
	std::cout << "\n----- key_comp -----" << std::endl;
	{
		MULTISET<int> mymultiset;

		for (int i = 0; i < 5; i++)
			mymultiset.insert(i);

		MULTISET<int>::key_compare mycomp = mymultiset.key_comp();

		std::cout << "mymultiset contains:";

		int highest = *mymultiset.rbegin();

		MULTISET<int>::iterator it = mymultiset.begin();
		do
		{
			std::cout << ' ' << *it;
		} while (mycomp(*it++, highest));

		std::cout << '\n';
	}

	// value_comp
	std::cout << "\n----- value_comp -----" << std::endl;
	{
		MULTISET<int> mymultiset;

		MULTISET<int>::value_compare mycomp = mymultiset.value_comp();

		for (int i = 0; i < 7; i++)
			mymultiset.insert(i);

		std::cout << "mymultiset contains:";

		int highest = *mymultiset.rbegin();
		MULTISET<int>::iterator it = mymultiset.begin();
		do
		{
			std::cout << ' ' << *it;
		} while (mycomp(*it++, highest));

		std::cout << '\n';
	}

	// find
	std::cout << "\n----- find -----" << std::endl;
	{
		MULTISET<int> mymultiset;
		MULTISET<int>::iterator it;

		// set some initial values:
		for (int i = 1; i <= 5; i++)
			mymultiset.insert(i * 10); // 10 20 30 40 50

		it = mymultiset.find(20);
		mymultiset.erase(it);
		mymultiset.erase(mymultiset.find(40));

		std::cout << "mymultiset contains:";
		for (it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// count
	std::cout << "\n----- count -----" << std::endl;
	{
		int myints[] = {10, 73, 12, 22, 73, 73, 12};
		MULTISET<int> mymultiset(myints, myints + 7);

		std::cout << "73 appears " << mymultiset.count(73) << " times in mymultiset.\n";
	}

	// lower_bound
	std::cout << "\n----- lower_bound -----" << std::endl;
	{
		MULTISET<int> mymultiset;
		MULTISET<int>::iterator itlow, itup;

		for (int i = 1; i < 8; i++)
			mymultiset.insert(i * 10); // 10 20 30 40 50 60 70

		itlow = mymultiset.lower_bound(30); //       ^
		itup = mymultiset.upper_bound(40);	//             ^

		mymultiset.erase(itlow, itup); // 10 20 50 60 70

		std::cout << "mymultiset contains:";
		for (MULTISET<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// upper_bound
	std::cout << "\n----- upper_bound -----" << std::endl;
	{
		MULTISET<int> mymultiset;
		MULTISET<int>::iterator itlow, itup;

		for (int i = 1; i < 8; i++)
			mymultiset.insert(i * 10); // 10 20 30 40 50 60 70

		itlow = mymultiset.lower_bound(30); //       ^
		itup = mymultiset.upper_bound(40);	//             ^

		mymultiset.erase(itlow, itup); // 10 20 50 60 70

		std::cout << "mymultiset contains:";
		for (MULTISET<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// equal_range
	std::cout << "\n----- equal_range -----" << std::endl;
	{
		int myints[] = {77, 30, 16, 2, 30, 30};
		MULTISET<int> mymultiset(myints, myints + 6); // 2 16 30 30 30 77

		std::pair<MULTISET<int>::iterator, MULTISET<int>::iterator> ret = mymultiset.equal_range(30); //      ^        ^

		mymultiset.erase(ret.first, ret.second);

		std::cout << "mymultiset contains:";
		for (MULTISET<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// relational operators
	std::cout << "\n----- relational operators -----" << std::endl;
	{
		MULTISET<int> foo, bar;
		foo.insert(10);
		bar.insert(20);
		bar.insert(20);
		foo.insert(30);

		// foo ({10,30}) vs bar ({20,20}):
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
		int myints[] = {12, 75, 12, 35, 20, 35};
		MULTISET<int> first(myints, myints + 3);	   // 12,12,75
		MULTISET<int> second(myints + 3, myints + 6); // 20,35,35

		swap(first, second);

		std::cout << "first contains:";
		for (MULTISET<int>::iterator it = first.begin(); it != first.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "second contains:";
		for (MULTISET<int>::iterator it = second.begin(); it != second.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

    std::cout << "     <<< Multiset test end >>>" << std::endl;
}
