// map::value_comp
#include <iostream>
#include "map.hpp"

int main ()
{
  ft::map<char,int> mymap;

  mymap.insert(std::pair<char, int>('x', 1001));
  mymap.insert(std::pair<char, int>('y', 2002));
  mymap.insert(std::pair<char, int>('z', 3003));

  std::cout << "mymap contains:\n";

  std::pair<char,int> highest = *mymap.rbegin();          // last element

  ft::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );

  return 0;
}
