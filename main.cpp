// constructing lists
#include <iostream>
#include "list.hpp"

int main ()
{
  // constructors used in the same order as described above:
  ft::list<int> first;                                // empty list of ints
  ft::list<int> second (4,100);                       // four ints with value 100
  ft::list<int> third (second.begin(),second.end());  // iterating through second
  ft::list<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  ft::list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are: ";
  for (ft::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
    std::cout << *it << ' ';

  std::cout << '\n';

  return 0;
}
