/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:33:28 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 18:58:47 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

bool fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const int &lhs, const int &rhs) const
	{
		return lhs < rhs;
	}
};

void test_set(void)
{
	std::cout << "     <<< Set test start >>>" << std::endl;

	// (constructor)
	std::cout << "----- constructor test -----" << std::endl;
	{
		SET<int> first; // empty set of ints

		int myints[] = {10, 20, 30, 40, 50};
		SET<int> second(myints, myints + 5); // range

		SET<int> third(second); // a copy of second

		SET<int> fourth(second.begin(), second.end()); // iterator ctor.

		SET<int, classcomp> fifth; // class as Compare

		bool (*fn_pt)(int, int) = fncomp;
		SET<int, bool (*)(int, int)> sixth(fn_pt); // function pointer as Compare
	}

	// operator=
	std::cout << "\n----- operator= -----" << std::endl;
	{
		int myints[] = {12, 82, 37, 64, 15};
		SET<int> first(myints, myints + 5); // set with 5 ints
		SET<int> second;					 // empty set

		second = first;			 // now second contains the 5 ints
		first = SET<int>(); // and first is empty

		std::cout << "Size of first: " << int(first.size()) << '\n';
		std::cout << "Size of second: " << int(second.size()) << '\n';
	}

	// begin
	std::cout << "\n----- begin -----" << std::endl;
	{
		int myints[] = {75, 23, 65, 42, 13};
		SET<int> myset(myints, myints + 5);

		std::cout << "myset contains:";
		for (SET<int>::iterator it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;

		std::cout << '\n';
	}

	// end
	std::cout << "\n----- end -----" << std::endl;
	{
		int myints[] = {75, 23, 65, 42, 13};
		SET<int> myset(myints, myints + 5);

		std::cout << "myset contains:";
		for (SET<int>::iterator it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;

		std::cout << '\n';
	}

	// rbegin
	std::cout << "\n----- rbegin -----" << std::endl;
	{
		int myints[] = {21, 64, 17, 78, 49};
		SET<int> myset(myints, myints + 5);

		SET<int>::reverse_iterator rit;

		std::cout << "myset contains:";
		for (rit = myset.rbegin(); rit != myset.rend(); ++rit)
			std::cout << ' ' << *rit;

		std::cout << '\n';
	}

	// rend
	std::cout << "\n----- rend -----" << std::endl;
	{
		int myints[] = {21, 64, 17, 78, 49};
		SET<int> myset(myints, myints + 5);

		SET<int>::reverse_iterator rit;

		std::cout << "myset contains:";
		for (rit = myset.rbegin(); rit != myset.rend(); ++rit)
			std::cout << ' ' << *rit;

		std::cout << '\n';
	}

	// empty
	std::cout << "\n----- empty -----" << std::endl;
	{
		SET<int> myset;

		myset.insert(20);
		myset.insert(30);
		myset.insert(10);

		std::cout << "myset contains:";
		while (!myset.empty())
		{
			std::cout << ' ' << *myset.begin();
			myset.erase(myset.begin());
		}
		std::cout << '\n';
	}

	// size
	std::cout << "\n----- size -----" << std::endl;
	{
		SET<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i = 0; i < 10; ++i)
			myints.insert(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.insert(100);
		std::cout << "2. size: " << myints.size() << '\n';

		myints.erase(5);
		std::cout << "3. size: " << myints.size() << '\n';
	}

	// max_size
	std::cout << "\n----- max_size -----" << std::endl;
	{
		int i;
		SET<int> myset;

		if (myset.max_size() > 1000)
		{
			for (i = 0; i < 1000; i++)
				myset.insert(i);
			std::cout << "The set contains 1000 elements.\n";
		}
		else
			std::cout << "The set could not hold 1000 elements.\n";
	}

	// insert
	std::cout << "\n----- insert -----" << std::endl;
	{
		SET<int> myset;
		SET<int>::iterator it;
		std::pair<SET<int>::iterator, bool> ret;

		// set some initial values:
		for (int i = 1; i <= 5; ++i)
			myset.insert(i * 10); // set: 10 20 30 40 50

		ret = myset.insert(20); // no new element inserted

		if (ret.second == false)
			it = ret.first; // "it" now points to element 20

		myset.insert(it, 25); // max efficiency inserting
		myset.insert(it, 24); // max efficiency inserting
		myset.insert(it, 26); // no max efficiency inserting

		int myints[] = {5, 10, 15}; // 10 already in set, not inserted
		myset.insert(myints, myints + 3);

		std::cout << "myset contains:";
		for (it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// erase
	std::cout << "\n----- erase -----" << std::endl;
	{
		SET<int> myset;
		SET<int>::iterator it;

		// insert some values:
		for (int i = 1; i < 10; i++)
			myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

		it = myset.begin();
		++it; // "it" points now to 20

		myset.erase(it);

		myset.erase(40);

		it = myset.find(60);
		myset.erase(it, myset.end());

		std::cout << "myset contains:";
		for (it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// swap
	std::cout << "\n----- swap -----" << std::endl;
	{
		int myints[] = {12, 75, 10, 32, 20, 25};
		SET<int> first(myints, myints + 3);	  // 10,12,75
		SET<int> second(myints + 3, myints + 6); // 20,25,32

		first.swap(second);

		std::cout << "first contains:";
		for (SET<int>::iterator it = first.begin(); it != first.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "second contains:";
		for (SET<int>::iterator it = second.begin(); it != second.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// clear
	std::cout << "\n----- clear -----" << std::endl;
	{
		SET<int> myset;

		myset.insert(100);
		myset.insert(200);
		myset.insert(300);

		std::cout << "myset contains:";
		for (SET<int>::iterator it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		myset.clear();
		myset.insert(1101);
		myset.insert(2202);

		std::cout << "myset contains:";
		for (SET<int>::iterator it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// key_comp
	std::cout << "\n----- key_comp -----" << std::endl;
	{
		SET<int> myset;
		int highest;

		SET<int>::key_compare mycomp = myset.key_comp();

		for (int i = 0; i <= 5; i++)
			myset.insert(i);

		std::cout << "myset contains:";

		highest = *myset.rbegin();
		SET<int>::iterator it = myset.begin();
		do
		{
			std::cout << ' ' << *it;
		} while (mycomp(*(++it), highest));

		std::cout << '\n';
	}

	// value_comp
	std::cout << "\n----- value_comp -----" << std::endl;
	{
		SET<int> myset;

		SET<int>::value_compare mycomp = myset.value_comp();

		for (int i = 0; i <= 5; i++)
			myset.insert(i);

		std::cout << "myset contains:";

		int highest = *myset.rbegin();
		SET<int>::iterator it = myset.begin();
		do
		{
			std::cout << ' ' << *it;
		} while (mycomp(*(++it), highest));

		std::cout << '\n';
	}

	// find
	std::cout << "\n----- find -----" << std::endl;
	{
		SET<int> myset;
		SET<int>::iterator it;

		// set some initial values:
		for (int i = 1; i <= 5; i++)
			myset.insert(i * 10); // set: 10 20 30 40 50

		it = myset.find(20);
		myset.erase(it);
		myset.erase(myset.find(40));

		std::cout << "myset contains:";
		for (it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// count
	std::cout << "\n----- count -----" << std::endl;
	{
		SET<int> myset;

		// set some initial values:
		for (int i = 1; i < 5; ++i)
			myset.insert(i * 3); // set: 3 6 9 12

		for (int i = 0; i < 10; ++i)
		{
			std::cout << i;
			if (myset.count(i) != 0)
				std::cout << " is an element of myset.\n";
			else
				std::cout << " is not an element of myset.\n";
		}
	}

	// lower_bound
	std::cout << "\n----- lower_bound -----" << std::endl;
	{
		SET<int> myset;
		SET<int>::iterator itlow, itup;

		for (int i = 1; i < 10; i++)
			myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

		itlow = myset.lower_bound(30); //       ^
		itup = myset.upper_bound(60);  //                   ^

		myset.erase(itlow, itup); // 10 20 70 80 90

		std::cout << "myset contains:";
		for (SET<int>::iterator it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// upper_bound
	std::cout << "\n----- upper_bound -----" << std::endl;
	{
		SET<int> myset;
		SET<int>::iterator itlow, itup;

		for (int i = 1; i < 10; i++)
			myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

		itlow = myset.lower_bound(30); //       ^
		itup = myset.upper_bound(60);  //                   ^

		myset.erase(itlow, itup); // 10 20 70 80 90

		std::cout << "myset contains:";
		for (SET<int>::iterator it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// equal_range
	std::cout << "\n----- equal_range -----" << std::endl;
	{
		SET<int> myset;

		for (int i = 1; i <= 5; i++)
			myset.insert(i * 10); // myset: 10 20 30 40 50

		std::pair<SET<int>::const_iterator, SET<int>::const_iterator> ret;
		ret = myset.equal_range(30);

		std::cout << "the lower bound points to: " << *ret.first << '\n';
		std::cout << "the upper bound points to: " << *ret.second << '\n';
	}

	// relational operators
	std::cout << "\n----- relational operators -----" << std::endl;
	{
		SET<int> foo, bar;
		foo.insert(10);
		bar.insert(20);
		bar.insert(30);
		foo.insert(40);

		// foo ({10,40}) vs bar ({20,30}):
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
		int myints[] = {12, 75, 10, 32, 20, 25};
		SET<int> first(myints, myints + 3);	  // 10,12,75
		SET<int> second(myints + 3, myints + 6); // 20,25,32

		swap(first, second);

		std::cout << "first contains:";
		for (SET<int>::iterator it = first.begin(); it != first.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "second contains:";
		for (SET<int>::iterator it = second.begin(); it != second.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	std::cout << "     <<< Set test end >>>" << std::endl;
}
