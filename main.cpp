// vector assignment
#include <iostream>
#include "vector.hpp"

int main()
{
    ft::vector<int> foo(3, 0);
    ft::vector<int> bar(5, 0);

    bar = foo;
    foo = ft::vector<int>();

    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
    return 0;
}
