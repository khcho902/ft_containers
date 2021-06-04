// set::begin/end
#include <iostream>
#include "set.hpp"

int main ()
{
  int myints[] = {75,23,65,42,13};
  ft::set<int> myset (myints,myints+5);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
  {
    std::cout << ' ' << *it;
  }

  std::cout << '\n';

  return 0;
}
