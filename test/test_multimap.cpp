/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_multimap.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:06:16 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 20:22:25 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

bool multi_fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{
		return lhs < rhs;
	}
};

void test_multimap(void)
{
	std::cout << "     <<< Multimap test start >>>" << std::endl;

	// (constructor)
	std::cout << "----- constructor test -----" << std::endl;
	{
		MULTIMAP<char, int> first;

		first.insert(std::pair<char, int>('a', 10));
		first.insert(std::pair<char, int>('b', 15));
		first.insert(std::pair<char, int>('b', 20));
		first.insert(std::pair<char, int>('c', 25));

		MULTIMAP<char, int> second(first.begin(), first.end());

		MULTIMAP<char, int> third(second);

		MULTIMAP<char, int, classcomp> fourth; // class as Compare

		bool (*fn_pt)(char, char) = multi_fncomp;
		MULTIMAP<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as comp
	}

	// operator=
	std::cout << "\n----- operator= -----" << std::endl;
	{
		MULTIMAP<char, int> foo, bar;

		foo.insert(std::make_pair('x', 32));
		foo.insert(std::make_pair('y', 64));
		foo.insert(std::make_pair('y', 96));
		foo.insert(std::make_pair('z', 128));

		bar = foo;	 // bar now contains 4 ints
		foo.clear(); // and first is now empty

		std::cout << "Size of foo: " << foo.size() << '\n';
		std::cout << "Size of bar: " << bar.size() << '\n';
	}

	// begin
	std::cout << "\n----- begin -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;

		mymultimap.insert(std::pair<char, int>('a', 10));
		mymultimap.insert(std::pair<char, int>('b', 20));
		mymultimap.insert(std::pair<char, int>('b', 150));

		// show content:
		for (MULTIMAP<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';
	}

	// end
	std::cout << "\n----- end -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;

		mymultimap.insert(std::pair<char, int>('a', 10));
		mymultimap.insert(std::pair<char, int>('b', 20));
		mymultimap.insert(std::pair<char, int>('b', 150));

		// show content:
		for (MULTIMAP<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';
	}

	// rbegin
	std::cout << "\n----- rbegin -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;

		mymultimap.insert(std::make_pair('x', 10));
		mymultimap.insert(std::make_pair('y', 20));
		mymultimap.insert(std::make_pair('y', 150));
		mymultimap.insert(std::make_pair('z', 9));

		// show content:
		MULTIMAP<char, int>::reverse_iterator rit;
		for (rit = mymultimap.rbegin(); rit != mymultimap.rend(); ++rit)
			std::cout << rit->first << " => " << rit->second << '\n';
	}

	// rend
	std::cout << "\n----- rend -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;

		mymultimap.insert(std::make_pair('x', 10));
		mymultimap.insert(std::make_pair('y', 20));
		mymultimap.insert(std::make_pair('y', 150));
		mymultimap.insert(std::make_pair('z', 9));

		// show content:
		MULTIMAP<char, int>::reverse_iterator rit;
		for (rit = mymultimap.rbegin(); rit != mymultimap.rend(); ++rit)
			std::cout << rit->first << " => " << rit->second << '\n';
	}

	// empty
	std::cout << "\n----- empty -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;

		mymultimap.insert(std::pair<char, int>('b', 101));
		mymultimap.insert(std::pair<char, int>('b', 202));
		mymultimap.insert(std::pair<char, int>('q', 505));

		while (!mymultimap.empty())
		{
			std::cout << mymultimap.begin()->first << " => ";
			std::cout << mymultimap.begin()->second << '\n';
			mymultimap.erase(mymultimap.begin());
		}
	}

	// size
	std::cout << "\n----- size -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;

		mymultimap.insert(std::make_pair('x', 100));
		mymultimap.insert(std::make_pair('y', 200));
		mymultimap.insert(std::make_pair('y', 350));
		mymultimap.insert(std::make_pair('z', 500));

		std::cout << "mymultimap.size() is " << mymultimap.size() << '\n';
	}
	
	// max_size
	std::cout << "\n----- max_size -----" << std::endl;
	{
		MULTIMAP<int, int> mymultimap;

		if (mymultimap.max_size() >= 1000u)
		{
			for (int i = 0; i < 1000; i++)
				mymultimap.insert(std::make_pair(i, 0));
			std::cout << "The multimap contains 1000 elements.\n";
		}
		else
			std::cout << "The multimap could not hold 1000 elements.\n";
	}

	// insert
	std::cout << "\n----- insert -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;
		MULTIMAP<char, int>::iterator it;

		// first insert function version (single parameter):
		mymultimap.insert(std::pair<char, int>('a', 100));
		mymultimap.insert(std::pair<char, int>('z', 150));
		it = mymultimap.insert(std::pair<char, int>('b', 75));

		// second insert function version (with hint position):
		mymultimap.insert(it, std::pair<char, int>('c', 300)); // max efficiency inserting
		mymultimap.insert(it, std::pair<char, int>('z', 400)); // no max efficiency inserting

		// third insert function version (range insertion):
		MULTIMAP<char, int> anothermultimap;
		anothermultimap.insert(mymultimap.begin(), mymultimap.find('c'));

		// showing contents:
		std::cout << "mymultimap contains:\n";
		for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';

		std::cout << "anothermultimap contains:\n";
		for (it = anothermultimap.begin(); it != anothermultimap.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';
	}

	// erase
	std::cout << "\n----- erase -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;

		// insert some values:
		mymultimap.insert(std::pair<char, int>('a', 10));
		mymultimap.insert(std::pair<char, int>('b', 20));
		mymultimap.insert(std::pair<char, int>('b', 30));
		mymultimap.insert(std::pair<char, int>('c', 40));
		mymultimap.insert(std::pair<char, int>('d', 50));
		mymultimap.insert(std::pair<char, int>('d', 60));
		mymultimap.insert(std::pair<char, int>('e', 70));
		mymultimap.insert(std::pair<char, int>('f', 80));

		MULTIMAP<char, int>::iterator it = mymultimap.find('b');

		mymultimap.erase(it); // erasing by iterator (1 element)

		mymultimap.erase('d'); // erasing by key (2 elements)

		it = mymultimap.find('e');
		mymultimap.erase(it, mymultimap.end()); // erasing by range

		// show content:
		for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';
	}

	// swap
	std::cout << "\n----- swap -----" << std::endl;
	{
		MULTIMAP<char, int> foo, bar;

		foo.insert(std::make_pair('x', 100));
		foo.insert(std::make_pair('y', 200));

		bar.insert(std::make_pair('a', 11));
		bar.insert(std::make_pair('b', 22));
		bar.insert(std::make_pair('a', 55));

		foo.swap(bar);

		std::cout << "foo contains:\n";
		for (MULTIMAP<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';

		std::cout << "bar contains:\n";
		for (MULTIMAP<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';
	}

	// clear
	std::cout << "\n----- clear -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;
		MULTIMAP<char, int>::iterator it;

		mymultimap.insert(std::pair<char, int>('b', 80));
		mymultimap.insert(std::pair<char, int>('b', 120));
		mymultimap.insert(std::pair<char, int>('q', 360));

		std::cout << "mymultimap contains:\n";
		for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';

		mymultimap.clear();

		mymultimap.insert(std::pair<char, int>('a', 11));
		mymultimap.insert(std::pair<char, int>('x', 22));

		std::cout << "mymultimap contains:\n";
		for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';
	}

	// key_comp
	std::cout << "\n----- key_comp -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;

		MULTIMAP<char, int>::key_compare mycomp = mymultimap.key_comp();

		mymultimap.insert(std::make_pair('a', 100));
		mymultimap.insert(std::make_pair('b', 200));
		mymultimap.insert(std::make_pair('b', 211));
		mymultimap.insert(std::make_pair('c', 300));

		std::cout << "mymultimap contains:\n";

		char highest = mymultimap.rbegin()->first; // key value of last element

		MULTIMAP<char, int>::iterator it = mymultimap.begin();
		do
		{
			std::cout << (*it).first << " => " << (*it).second << '\n';
		} while (mycomp((*it++).first, highest));

		std::cout << '\n';
	}

	// value_comp
	std::cout << "\n----- value_comp -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;

		mymultimap.insert(std::make_pair('x', 101));
		mymultimap.insert(std::make_pair('y', 202));
		mymultimap.insert(std::make_pair('y', 252));
		mymultimap.insert(std::make_pair('z', 303));

		std::cout << "mymultimap contains:\n";

		std::pair<char, int> highest = *mymultimap.rbegin(); // last element

		MULTIMAP<char, int>::iterator it = mymultimap.begin();
		do
		{
			std::cout << (*it).first << " => " << (*it).second << '\n';
		} while (mymultimap.value_comp()(*it++, highest));
	}

	// find
	std::cout << "\n----- find -----" << std::endl;
	{
		MULTIMAP<char, int> mymm;

		mymm.insert(std::make_pair('x', 10));
		mymm.insert(std::make_pair('y', 20));
		mymm.insert(std::make_pair('z', 30));
		mymm.insert(std::make_pair('z', 40));

		MULTIMAP<char, int>::iterator it = mymm.find('x');
		mymm.erase(it);
		mymm.erase(mymm.find('z'));

		// print content:
		std::cout << "elements in mymm:" << '\n';
		std::cout << "y => " << mymm.find('y')->second << '\n';
		std::cout << "z => " << mymm.find('z')->second << '\n';
	}

	// count
	std::cout << "\n----- count -----" << std::endl;
	{
		MULTIMAP<char, int> mymm;

		mymm.insert(std::make_pair('x', 50));
		mymm.insert(std::make_pair('y', 100));
		mymm.insert(std::make_pair('y', 150));
		mymm.insert(std::make_pair('y', 200));
		mymm.insert(std::make_pair('z', 250));
		mymm.insert(std::make_pair('z', 300));

		for (char c = 'x'; c <= 'z'; c++)
		{
			std::cout << "There are " << mymm.count(c) << " elements with key " << c << ":";
			MULTIMAP<char, int>::iterator it;
			for (it = mymm.equal_range(c).first; it != mymm.equal_range(c).second; ++it)
				std::cout << ' ' << (*it).second;
			std::cout << '\n';
		}
	}

	// lower_bound
	std::cout << "\n----- lower_bound -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;
		MULTIMAP<char, int>::iterator it, itlow, itup;

		mymultimap.insert(std::make_pair('a', 10));
		mymultimap.insert(std::make_pair('b', 121));
		mymultimap.insert(std::make_pair('c', 1001));
		mymultimap.insert(std::make_pair('c', 2002));
		mymultimap.insert(std::make_pair('d', 11011));
		mymultimap.insert(std::make_pair('e', 44));

		itlow = mymultimap.lower_bound('b'); // itlow points to b
		itup = mymultimap.upper_bound('d');	 // itup points to e (not d)

		// print range [itlow,itup):
		for (it = itlow; it != itup; ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';
	}

	// upper_bound
	std::cout << "\n----- upper_bound -----" << std::endl;
	{
		MULTIMAP<char, int> mymultimap;
		MULTIMAP<char, int>::iterator it, itlow, itup;

		mymultimap.insert(std::make_pair('a', 10));
		mymultimap.insert(std::make_pair('b', 121));
		mymultimap.insert(std::make_pair('c', 1001));
		mymultimap.insert(std::make_pair('c', 2002));
		mymultimap.insert(std::make_pair('d', 11011));
		mymultimap.insert(std::make_pair('e', 44));

		itlow = mymultimap.lower_bound('b'); // itlow points to b
		itup = mymultimap.upper_bound('d');	 // itup points to e (not d)

		// print range [itlow,itup):
		for (it = itlow; it != itup; ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';
	}

	// equal_range
	std::cout << "\n----- equal_range -----" << std::endl;
	{
		MULTIMAP<char, int> mymm;

		mymm.insert(std::pair<char, int>('a', 10));
		mymm.insert(std::pair<char, int>('b', 20));
		mymm.insert(std::pair<char, int>('b', 30));
		mymm.insert(std::pair<char, int>('b', 40));
		mymm.insert(std::pair<char, int>('c', 50));
		mymm.insert(std::pair<char, int>('c', 60));
		mymm.insert(std::pair<char, int>('d', 60));

		std::cout << "mymm contains:\n";
		for (char ch = 'a'; ch <= 'd'; ch++)
		{
			std::pair<MULTIMAP<char, int>::iterator, MULTIMAP<char, int>::iterator> ret;
			ret = mymm.equal_range(ch);
			std::cout << ch << " =>";
			for (MULTIMAP<char, int>::iterator it = ret.first; it != ret.second; ++it)
				std::cout << ' ' << it->second;
			std::cout << '\n';
		}
	}

	// relational operators
	std::cout << "\n----- relational operators -----" << std::endl;
	{
		MULTIMAP<char, int> foo, bar;

		foo.insert(std::make_pair('a', 100));
		foo.insert(std::make_pair('z', 900));
		bar.insert(std::make_pair('b', 250));
		bar.insert(std::make_pair('b', 350));

		// foo ({{a,100},{z,900}}) vs bar ({b,250},{b,350}}):
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
		MULTIMAP<char, int> foo, bar;

		foo.insert(std::make_pair('x', 100));
		foo.insert(std::make_pair('y', 200));

		bar.insert(std::make_pair('a', 11));
		bar.insert(std::make_pair('b', 22));
		bar.insert(std::make_pair('a', 55));

		swap(foo, bar);

		std::cout << "foo contains:\n";
		for (MULTIMAP<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';

		std::cout << "bar contains:\n";
		for (MULTIMAP<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << (*it).first << " => " << (*it).second << '\n';
	}

    std::cout << "     <<< Multimap test end >>>" << std::endl;
}
