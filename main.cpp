// list::merge
#include <iostream>
#include "list.hpp"

// compare only integral part:
bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

int main ()
{
  ft::list<double> first, second;

  first.push_back (2.2);
  first.push_back (2.9);
  first.push_back (3.1);
  first.push_back (3.1);
  first.push_back (3.1);
  first.push_back (3.1);
  first.push_back (100.1);

  second.push_back (1.4);
  second.push_back (3.7);
  second.push_back (7.1);
  second.push_back (7.1);
  second.push_back (7.1);
  second.push_back (7.1);
  second.push_back (7.1);


  //first.sort();
  //second.sort();

  first.merge(second);

  // (second is now empty)

  second.push_back (2.1);

  first.merge(second,mycomparison);

  std::cout << "first contains:";
  for (ft::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
