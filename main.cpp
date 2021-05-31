// stack::push/pop
#include <iostream>       // std::cout
//#include <stack>          // std::stack
#include "stack.hpp"

int main ()
{
  ft::stack<int> mystack;

  for (int i=0; i<5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  while (!mystack.empty())
  {
     std::cout << ' ' << mystack.top();
     mystack.pop();
  }
  std::cout << '\n';

return 0;
}
