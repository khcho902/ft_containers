/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:40:38 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 19:06:46 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{
		return lhs < rhs;
	}
};

void test_map(void)
{
	std::cout << "     <<< Map test start >>>" << std::endl;

	// (constructor)
	std::cout << "----- constructor test -----" << std::endl;
	{
		MAP<char, int> first;

		first['a'] = 10;
		first['b'] = 30;
		first['c'] = 50;
		first['d'] = 70;

		MAP<char, int> second(first.begin(), first.end());

		MAP<char, int> third(second);

		MAP<char, int, classcomp> fourth; // class as Compare

		bool (*fn_pt)(char, char) = fncomp;
		MAP<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare
	}

	// operator=
	std::cout << "\n----- operator= -----" << std::endl;
	{
		MAP<char, int> first;
		MAP<char, int> second;

		first['x'] = 8;
		first['y'] = 16;
		first['z'] = 32;

		second = first;				   // second now contains 3 ints
		first = MAP<char, int>(); // and first is now empty

		std::cout << "Size of first: " << first.size() << '\n';
		std::cout << "Size of second: " << second.size() << '\n';
	}

	// begin
	std::cout << "\n----- begin -----" << std::endl;
	{
		MAP<char, int> mymap;

		mymap['b'] = 100;
		mymap['a'] = 200;
		mymap['c'] = 300;

		// show content:
		for (MAP<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	// end
	std::cout << "\n----- end -----" << std::endl;
	{
		MAP<char, int> mymap;

		mymap['b'] = 100;
		mymap['a'] = 200;
		mymap['c'] = 300;

		// show content:
		for (MAP<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	// rbegin
	std::cout << "\n----- rbegin -----" << std::endl;
	{
		MAP<char, int> mymap;

		mymap['x'] = 100;
		mymap['y'] = 200;
		mymap['z'] = 300;

		// show content:
		MAP<char, int>::reverse_iterator rit;
		for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
			std::cout << rit->first << " => " << rit->second << '\n';
	}

	// rend
	std::cout << "\n----- rend -----" << std::endl;
	{
		MAP<char, int> mymap;

		mymap['x'] = 100;
		mymap['y'] = 200;
		mymap['z'] = 300;

		// show content:
		MAP<char, int>::reverse_iterator rit;
		for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
			std::cout << rit->first << " => " << rit->second << '\n';
	}

	// empty
	std::cout << "\n----- empty -----" << std::endl;
	{
		MAP<char, int> mymap;

		mymap['a'] = 10;
		mymap['b'] = 20;
		mymap['c'] = 30;

		while (!mymap.empty())
		{
			std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
			mymap.erase(mymap.begin());
		}
	}

	// size
	std::cout << "\n----- size -----" << std::endl;
	{
		MAP<char, int> mymap;
		mymap['a'] = 101;
		mymap['b'] = 202;
		mymap['c'] = 302;

		std::cout << "mymap.size() is " << mymap.size() << '\n';
	}

	// max_size
	std::cout << "\n----- max_size -----" << std::endl;
	{
		int i;
		MAP<int, int> mymap;

		if (mymap.max_size() > 1000)
		{
			for (i = 0; i < 1000; i++)
				mymap[i] = 0;
			std::cout << "The map contains 1000 elements.\n";
		}
		else
			std::cout << "The map could not hold 1000 elements.\n";
	}

	// operator[]
	std::cout << "\n----- operator[] -----" << std::endl;
	{
		MAP<char, std::string> mymap;

		mymap['a'] = "an element";
		mymap['b'] = "another element";
		mymap['c'] = mymap['b'];

		std::cout << "mymap['a'] is " << mymap['a'] << '\n';
		std::cout << "mymap['b'] is " << mymap['b'] << '\n';
		std::cout << "mymap['c'] is " << mymap['c'] << '\n';
		std::cout << "mymap['d'] is " << mymap['d'] << '\n';

		std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	}

	// insert
	std::cout << "\n----- insert -----" << std::endl;
	{
		MAP<char, int> mymap;

		// first insert function version (single parameter):
		mymap.insert(std::pair<char, int>('a', 100));
		mymap.insert(std::pair<char, int>('z', 200));

		std::pair<MAP<char, int>::iterator, bool> ret;
		ret = mymap.insert(std::pair<char, int>('z', 500));
		if (ret.second == false)
		{
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		MAP<char, int>::iterator it = mymap.begin();
		mymap.insert(it, std::pair<char, int>('b', 300)); // max efficiency inserting
		mymap.insert(it, std::pair<char, int>('c', 400)); // no max efficiency inserting

		// third insert function version (range insertion):
		MAP<char, int> anothermap;
		anothermap.insert(mymap.begin(), mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "anothermap contains:\n";
		for (it = anothermap.begin(); it != anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	
	// erase
	std::cout << "\n----- erase -----" << std::endl;
	{
		MAP<char, int> mymap;
		MAP<char, int>::iterator it;

		// insert some values:
		mymap['a'] = 10;
		mymap['b'] = 20;
		mymap['c'] = 30;
		mymap['d'] = 40;
		mymap['e'] = 50;
		mymap['f'] = 60;

		it = mymap.find('b');
		mymap.erase(it); // erasing by iterator

		mymap.erase('c'); // erasing by key

		it = mymap.find('e');
		mymap.erase(it, mymap.end()); // erasing by range

		// show content:
		for (it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	// swap
	std::cout << "\n----- swap -----" << std::endl;
	{
		MAP<char, int> foo, bar;

		foo['x'] = 100;
		foo['y'] = 200;

		bar['a'] = 11;
		bar['b'] = 22;
		bar['c'] = 33;

		foo.swap(bar);

		std::cout << "foo contains:\n";
		for (MAP<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "bar contains:\n";
		for (MAP<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	// clear
	std::cout << "\n----- clear -----" << std::endl;
	{
		MAP<char, int> mymap;

		mymap['x'] = 100;
		mymap['y'] = 200;
		mymap['z'] = 300;

		std::cout << "mymap contains:\n";
		for (MAP<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		mymap.clear();
		mymap['a'] = 1101;
		mymap['b'] = 2202;

		std::cout << "mymap contains:\n";
		for (MAP<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	// key_comp
	std::cout << "\n----- key_comp -----" << std::endl;
	{
		MAP<char, int> mymap;

		MAP<char, int>::key_compare mycomp = mymap.key_comp();

		mymap['a'] = 100;
		mymap['b'] = 200;
		mymap['c'] = 300;

		std::cout << "mymap contains:\n";

		char highest = mymap.rbegin()->first; // key value of last element

		MAP<char, int>::iterator it = mymap.begin();
		do
		{
			std::cout << it->first << " => " << it->second << '\n';
		} while (mycomp((*it++).first, highest));

		std::cout << '\n';
	}

	// value_comp
	std::cout << "\n----- value_comp -----" << std::endl;
	{
		MAP<char, int> mymap;

		mymap['x'] = 1001;
		mymap['y'] = 2002;
		mymap['z'] = 3003;

		std::cout << "mymap contains:\n";

		std::pair<char, int> highest = *mymap.rbegin(); // last element

		MAP<char, int>::iterator it = mymap.begin();
		do
		{
			std::cout << it->first << " => " << it->second << '\n';
		} while (mymap.value_comp()(*it++, highest));
	}

	// find
	std::cout << "\n----- find -----" << std::endl;
	{
		MAP<char, int> mymap;
		MAP<char, int>::iterator it;

		mymap['a'] = 50;
		mymap['b'] = 100;
		mymap['c'] = 150;
		mymap['d'] = 200;

		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase(it);

		// print content:
		std::cout << "elements in mymap:" << '\n';
		std::cout << "a => " << mymap.find('a')->second << '\n';
		std::cout << "c => " << mymap.find('c')->second << '\n';
		std::cout << "d => " << mymap.find('d')->second << '\n';
	}

	// count
	std::cout << "\n----- count -----" << std::endl;
	{
		MAP<char, int> mymap;
		char c;

		mymap['a'] = 101;
		mymap['c'] = 202;
		mymap['f'] = 303;

		for (c = 'a'; c < 'h'; c++)
		{
			std::cout << c;
			if (mymap.count(c) > 0)
				std::cout << " is an element of mymap.\n";
			else
				std::cout << " is not an element of mymap.\n";
		}
	}

	// lower_bound
	std::cout << "\n----- lower_bound -----" << std::endl;
	{
		MAP<char, int> mymap;
		MAP<char, int>::iterator itlow, itup;

		mymap['a'] = 20;
		mymap['b'] = 40;
		mymap['c'] = 60;
		mymap['d'] = 80;
		mymap['e'] = 100;

		itlow = mymap.lower_bound('b'); // itlow points to b
		itup = mymap.upper_bound('d');	// itup points to e (not d!)

		mymap.erase(itlow, itup); // erases [itlow,itup)

		// print content:
		for (MAP<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	// upper_bound
	std::cout << "\n----- upper_bound -----" << std::endl;
	{
		MAP<char, int> mymap;
		MAP<char, int>::iterator itlow, itup;

		mymap['a'] = 20;
		mymap['b'] = 40;
		mymap['c'] = 60;
		mymap['d'] = 80;
		mymap['e'] = 100;

		itlow = mymap.lower_bound('b'); // itlow points to b
		itup = mymap.upper_bound('d');	// itup points to e (not d!)

		mymap.erase(itlow, itup); // erases [itlow,itup)

		// print content:
		for (MAP<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	
	// equal_range
	std::cout << "\n----- equal_range -----" << std::endl;
	{
		MAP<char, int> mymap;

		mymap['a'] = 10;
		mymap['b'] = 20;
		mymap['c'] = 30;

		std::pair<MAP<char, int>::iterator, MAP<char, int>::iterator> ret;
		ret = mymap.equal_range('b');

		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';

		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
	}

	// relational operators
	std::cout << "\n----- relational operators -----" << std::endl;
	{
		MAP<char, int> foo, bar;
		foo['a'] = 100;
		foo['b'] = 200;
		bar['a'] = 10;
		bar['z'] = 1000;

		// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
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
		MAP<char, int> foo, bar;

		foo['x'] = 100;
		foo['y'] = 200;

		bar['a'] = 11;
		bar['b'] = 22;
		bar['c'] = 33;

		swap(foo, bar);

		std::cout << "foo contains:\n";
		for (MAP<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "bar contains:\n";
		for (MAP<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

    std::cout << "     <<< Map test end >>>" << std::endl;
}
