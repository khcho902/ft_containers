// list::assign
#include <iostream>
#include "list.hpp"

int main ()
{
	typedef ft::list<int>::iterator iterator;

  ft::list<int> first;
  ft::list<int> second;

  first.assign(7,100);                      // 7 ints with value 100

  std::cout << "first list : " ;
  for (iterator it = first.begin(); it != first.end(); it++)
  {
	  std::cout << *it << " ";
  }
  std::cout << std::endl;


  second.assign(first.begin(),first.end()); // a copy of first


  std::cout << "second list : " ;
  for (iterator it = second.begin(); it != second.end(); it++)
  {
	  std::cout << *it << " ";
  }
  std::cout << std::endl;

  int myints[]={1776,7,4};
  first.assign(myints,myints+3);            // assigning from array

  std::cout << "first list : " ;
  for (iterator it = first.begin(); it != first.end(); it++)
  {
	  std::cout << *it << " ";
  }
  std::cout << std::endl;



  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  return 0;
}
