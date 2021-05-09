#include <iostream>
//#include <list>
#include "list.hpp"

int main ()
{
  ft::list<int> mylist;
  
  for (int i=1; i<=5; ++i)
  	mylist.push_back(i);

  std::cout << "mylist backwards:";
  for (ft::list<int>::reverse_iterator rit = mylist.rbegin(); rit!=mylist.rend(); ++rit)
  {
    std::cout << ' ' << *rit;
  }

  std::cout << '\n';

  return 0;
}