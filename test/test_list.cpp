/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:09:19 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 21:56:01 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

// a predicate implemented as a function:
bool single_digit(const int &value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd
{
    bool operator()(const int &value) { return (value % 2) == 1; }
};

// a binary predicate implemented as a function:
bool same_integral_part(double first, double second)
{
    return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near
{
    bool operator()(double first, double second)
    {
        return (fabs(first - second) < 5.0);
    }
};

// compare only integral part:
bool mycomparison(double first, double second)
{
    return (int(first) < int(second));
}

// comparison, not case sensitive.
bool compare_nocase(const std::string &first, const std::string &second)
{
    unsigned int i = 0;
    while ((i < first.length()) && (i < second.length()))
    {
        if (tolower(first[i]) < tolower(second[i]))
            return true;
        else if (tolower(first[i]) > tolower(second[i]))
            return false;
        ++i;
    }
    return (first.length() < second.length());
}

void test_list(void)
{
	std::cout << "     <<< List test start >>>" << std::endl;

    // (constructor)
    std::cout << "----- constructor -----" << std::endl;
    {
        // constructors used in the same order as described above:
        LIST<int> first;                               // empty list of ints
        LIST<int> second(4, 100);                      // four ints with value 100
        LIST<int> third(second.begin(), second.end()); // iterating through second
        LIST<int> fourth(third);                       // a copy of third
        
        // the iterator constructor can also be used to construct from arrays:
        int myints[] = {16, 2, 77, 29};
        LIST<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
        
        std::cout << "The contents of fifth are: ";
        for (LIST<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

    // operator=
    std::cout << "\n----- operator= -----" << std::endl;
    {

        LIST<int> first (3);      // list of 3 zero-initialized ints
        LIST<int> second (5);     // list of 5 zero-initialized ints
        
        second = first;
        first = LIST<int>();
        
        std::cout << "Size of first: " << int (first.size()) << '\n';
        std::cout << "Size of second: " << int (second.size()) << '\n';
    }

    // begin
    std::cout << "\n----- begin -----" << std::endl;
    {
        int myints[] = {75, 23, 65, 42, 13};
        LIST<int> mylist(myints, myints + 5);

        std::cout << "mylist contains:";
        for (LIST<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << '\n';
    }

    // end
    std::cout << "\n----- end -----" << std::endl;
    {
        int myints[] = {75, 23, 65, 42, 13};
        LIST<int> mylist(myints, myints + 5);

        std::cout << "mylist contains:";
        for (LIST<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << '\n';
    }

    // rbegin
    std::cout << "\n----- rbegin -----" << std::endl;
    {
        LIST<int> mylist;
        for (int i = 1; i <= 5; ++i)
            mylist.push_back(i);

        std::cout << "mylist backwards:";
        for (LIST<int>::reverse_iterator rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
            std::cout << ' ' << *rit;

        std::cout << '\n';
    }

    // rend
    std::cout << "\n----- rend -----" << std::endl;
    {
        LIST<int> mylist;
        for (int i = 1; i <= 5; ++i)
            mylist.push_back(i);

        std::cout << "mylist backwards:";
        for (LIST<int>::reverse_iterator rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
            std::cout << ' ' << *rit;

        std::cout << '\n';
    }

    // empty
    std::cout << "\n----- empty -----" << std::endl;
    {
        LIST<int> mylist;
        int sum(0);

        for (int i = 1; i <= 10; ++i)
            mylist.push_back(i);

        while (!mylist.empty())
        {
            sum += mylist.front();
            mylist.pop_front();
        }

        std::cout << "total: " << sum << '\n';
    }

    // size
    std::cout << "\n----- size -----" << std::endl;
    {
        LIST<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i = 0; i < 10; i++)
            myints.push_back(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.insert(myints.begin(), 10, 100);
        std::cout << "2. size: " << myints.size() << '\n';

        myints.pop_back();
        std::cout << "3. size: " << myints.size() << '\n';
    }

    // max_size
    std::cout << "\n----- max_size -----" << std::endl;
    {
        unsigned int i;
        LIST<int> mylist;

        std::cout << "Enter number of elements: ";
        std::cin >> i;

        if (i < mylist.max_size())
            mylist.resize(i);
        else
            std::cout << "That size exceeds the limit.\n";
    }

    // front
    std::cout << "\n----- front -----" << std::endl;
    {
        LIST<int> mylist;

        mylist.push_back(77);
        mylist.push_back(22);

        // now front equals 77, and back 22

        mylist.front() -= mylist.back();

        std::cout << "mylist.front() is now " << mylist.front() << '\n';
    }

    // back
    std::cout << "\n-----back  -----" << std::endl;
    {
        LIST<int> mylist;

        mylist.push_back(10);

        while (mylist.back() != 0)
        {
            mylist.push_back(mylist.back() - 1);
        }

        std::cout << "mylist contains:";
        for (LIST<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << '\n';
    }

    // assign
    std::cout << "\n----- assign -----" << std::endl;
    {
        LIST<int> first;
        LIST<int> second;

        first.assign(7, 100); // 7 ints with value 100

        second.assign(first.begin(), first.end()); // a copy of first

        int myints[] = {1776, 7, 4};
        first.assign(myints, myints + 3); // assigning from array

        std::cout << "Size of first: " << int(first.size()) << '\n';
        std::cout << "Size of second: " << int(second.size()) << '\n';
    }

    // push_front
    std::cout << "\n----- push_front -----" << std::endl;
    {
        LIST<int> mylist(2, 100); // two ints with a value of 100
        mylist.push_front(200);
        mylist.push_front(300);

        std::cout << "mylist contains:";
        for (LIST<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << '\n';
    }

    // pop_front
    std::cout << "\n----- pop_front -----" << std::endl;
    {
        LIST<int> mylist;
        mylist.push_back(100);
        mylist.push_back(200);
        mylist.push_back(300);

        std::cout << "Popping out the elements in mylist:";
        while (!mylist.empty())
        {
            std::cout << ' ' << mylist.front();
            mylist.pop_front();
        }

        std::cout << "\nFinal size of mylist is " << mylist.size() << '\n';
    }

    // push_back
    std::cout << "\n----- push_back -----" << std::endl;
    {
        LIST<int> mylist;
        int myint;

        std::cout << "Please enter some integers (enter 0 to end):\n";

        do
        {
            std::cin >> myint;
            mylist.push_back(myint);
        } while (myint);

        std::cout << "mylist stores " << mylist.size() << " numbers.\n";
    }

    // pop_back
    std::cout << "\n----- pop_back -----" << std::endl;
    {
        LIST<int> mylist;
        int sum(0);
        mylist.push_back(100);
        mylist.push_back(200);
        mylist.push_back(300);

        while (!mylist.empty())
        {
            sum += mylist.back();
            mylist.pop_back();
        }

        std::cout << "The elements of mylist summed " << sum << '\n';
    }

    // insert
    std::cout << "\n----- insert -----" << std::endl;
    {
        LIST<int> mylist;
        LIST<int>::iterator it;

        // set some initial values:
        for (int i = 1; i <= 5; ++i)
            mylist.push_back(i);                // 1 2 3 4 5

        it = mylist.begin();
        ++it;       // it points now to number 2     ^

        mylist.insert(it, 10);                  // 1 10 2 3 4 5

        // "it" still points to number 2                ^
        mylist.insert(it, 2, 20);               // 1 10 20 20 2 3 4 5

        --it; // it points now to the second 20             ^

        VECTOR<int> myvector(2, 30);
        mylist.insert(it, myvector.begin(), myvector.end());
                                                // 1 10 20 30 30 20 2 3 4 5
                                                //               ^
        std::cout << "mylist contains:";
        for (it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    // erase
    std::cout << "\n----- erase -----" << std::endl;
    {
        LIST<int> mylist;
        LIST<int>::iterator it1, it2;

        // set some values:
        for (int i = 1; i < 10; ++i)
            mylist.push_back(i * 10);

                                    // 10 20 30 40 50 60 70 80 90
        it1 = it2 = mylist.begin(); // ^^
        std::advance(it2, 6);       // ^                 ^
        ++it1;                      //    ^              ^

        it1 = mylist.erase(it1);    // 10 30 40 50 60 70 80 90
                                    //    ^           ^

        it2 = mylist.erase(it2);    // 10 30 40 50 60 80 90
                                    //    ^           ^

        ++it1;                      //       ^        ^
        --it2;                      //       ^     ^

        mylist.erase(it1, it2);     // 10 30 60 80 90
                                    //        ^

        std::cout << "mylist contains:";
        for (it1 = mylist.begin(); it1 != mylist.end(); ++it1)
            std::cout << ' ' << *it1;
        std::cout << '\n';
    }

    // swap
    std::cout << "\n----- swap -----" << std::endl;
    {
        LIST<int> first(3, 100);  // three ints with a value of 100
        LIST<int> second(5, 200); // five ints with a value of 200

        first.swap(second);

        std::cout << "first contains:";
        for (LIST<int>::iterator it = first.begin(); it != first.end(); it++)
            std::cout << ' ' << *it;
        std::cout << '\n';

        std::cout << "second contains:";
        for (LIST<int>::iterator it = second.begin(); it != second.end(); it++)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    // resize
    std::cout << "\n----- resize -----" << std::endl;
    {
        LIST<int> mylist;

        // set some initial content:
        for (int i = 1; i < 10; ++i)
            mylist.push_back(i);

        mylist.resize(5);
        mylist.resize(8, 100);
        mylist.resize(12);

        std::cout << "mylist contains:";
        for (LIST<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << '\n';
    }

    // clear
    std::cout << "\n----- clear -----" << std::endl;
    {
        LIST<int> mylist;
        LIST<int>::iterator it;

        mylist.push_back(100);
        mylist.push_back(200);
        mylist.push_back(300);

        std::cout << "mylist contains:";
        for (it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

        mylist.clear();
        mylist.push_back(1101);
        mylist.push_back(2202);

        std::cout << "mylist contains:";
        for (it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    // splice
    std::cout << "\n----- splice -----" << std::endl;
    {
        LIST<int> mylist1, mylist2;
        LIST<int>::iterator it;
        
        // set some initial values:
        for (int i=1; i<=4; ++i)
            mylist1.push_back(i);       // mylist1: 1 2 3 4

        for (int i=1; i<=3; ++i)
            mylist2.push_back(i*10);    // mylist2: 10 20 30

        it = mylist1.begin();
            ++it;                       // points to 2

        mylist1.splice (it, mylist2);   // mylist1: 1 10 20 30 2 3 4
                                        // mylist2 (empty)
                                        // "it" still points to 2 (the 5th element)
                                          
        mylist2.splice (mylist2.begin(),mylist1, it);
                                        // mylist1: 1 10 20 30 3 4
                                        // mylist2: 2
                                        // "it" is now invalid.
        it = mylist1.begin();
        std::advance(it,3);             // "it" points now to 30

        mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
                                        // mylist1: 30 3 4 1 10 20

        std::cout << "mylist1 contains:";
        for (it=mylist1.begin(); it!=mylist1.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

        std::cout << "mylist2 contains:";
        for (it=mylist2.begin(); it!=mylist2.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    // remove
    std::cout << "\n----- remove -----" << std::endl;
    {
        int myints[] = {17, 89, 7, 14};
        LIST<int> mylist(myints, myints + 4);

        mylist.remove(89);

        std::cout << "mylist contains:";
        for (LIST<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    // remove_if
    std::cout << "\n----- remove_if -----" << std::endl;
    {
        int myints[] = {15, 36, 7, 17, 20, 39, 4, 1};
        LIST<int> mylist(myints, myints + 8); // 15 36 7 17 20 39 4 1

        mylist.remove_if(single_digit); // 15 36 17 20 39

        mylist.remove_if(is_odd()); // 36 20

        std::cout << "mylist contains:";
        for (LIST<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    // unique
    std::cout << "\n----- unique -----" << std::endl;
    {
        double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14, 
                            12.77, 73.35, 72.25, 15.3,  72.25 };
        LIST<double> mylist (mydoubles,mydoubles+10);
  
        mylist.sort();              //  2.72,  3.14, 12.15, 12.77, 12.77,
                                    // 15.3,  72.25, 72.25, 73.0,  73.35

        mylist.unique();            //  2.72,  3.14, 12.15, 12.77
                                    // 15.3,  72.25, 73.0,  73.35

        mylist.unique (same_integral_part); //  2.72,  3.14, 12.15
                                            // 15.3,  72.25, 73.0

        mylist.unique (is_near());           //  2.72, 12.15, 72.25

        std::cout << "mylist contains:";
        for (LIST<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    // merge
    std::cout << "\n----- merge -----" << std::endl;
    {
        LIST<double> first, second;

        first.push_back(3.1);
        first.push_back(2.2);
        first.push_back(2.9);

        second.push_back(3.7);
        second.push_back(7.1);
        second.push_back(1.4);

        first.sort();
        second.sort();

        first.merge(second);

        // (second is now empty)

        second.push_back(2.1);

        first.merge(second, mycomparison);

        std::cout << "first contains:";
        for (LIST<double>::iterator it = first.begin(); it != first.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }
    
    // sort
    std::cout << "\n----- sort -----" << std::endl;
    {
        LIST<std::string> mylist;
        LIST<std::string>::iterator it;
        mylist.push_back("one");
        mylist.push_back("two");
        mylist.push_back("Three");

        mylist.sort();

        std::cout << "mylist contains:";
        for (it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

        mylist.sort(compare_nocase);

        std::cout << "mylist contains:";
        for (it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    // reverse
    std::cout << "\n----- reverse -----" << std::endl;
    {
        LIST<int> mylist;

        for (int i = 1; i < 10; ++i)
            mylist.push_back(i);

        mylist.reverse();

        std::cout << "mylist contains:";
        for (LIST<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << '\n';
    }

    // relational operators (list)
    std::cout << "\n----- relational operators (list) -----" << std::endl;
    {
        LIST<int> a; //  = {10, 20, 30};
        a.push_back(10);
        a.push_back(20);
        a.push_back(30);

        LIST<int> b; //  = {10, 20, 30};
        b.push_back(10);
        b.push_back(20);
        b.push_back(30);

        LIST<int> c; //  = {30, 20, 10};
        c.push_back(30);
        c.push_back(20);
        c.push_back(10);

        if (a == b)
            std::cout << "a and b are equal\n";
        if (b != c)
            std::cout << "b and c are not equal\n";
        if (b < c)
            std::cout << "b is less than c\n";
        if (c > b)
            std::cout << "c is greater than b\n";
        if (a <= b)
            std::cout << "a is less than or equal to b\n";
        if (a >= b)
            std::cout << "a is greater than or equal to b\n";
    }

    // swap (non-member)
    std::cout << "\n----- swap (list) -----" << std::endl;
    {
        LIST<int> foo(3, 100); // three ints with a value of 100
        LIST<int> bar(5, 200); // five ints with a value of 200

        std::swap(foo, bar);

        std::cout << "foo contains:";
        for (LIST<int>::iterator it = foo.begin(); it != foo.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

        std::cout << "bar contains:";
        for (LIST<int>::iterator it = bar.begin(); it != bar.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    std::cout << "     <<< List test end >>>" << std::endl;
}
