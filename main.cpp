// swap vectors
#include <iostream>
#include "vector.hpp"

int main()
{
    ft::vector<int> foo;  //(3, 100); // three ints with a value of 100
    foo.push_back(100);
    foo.push_back(100);
    foo.push_back(100);

    ft::vector<int> bar;  //(5, 200); // five ints with a value of 200
    bar.push_back(200);
    bar.push_back(200);
    bar.push_back(200);
    bar.push_back(200);
    bar.push_back(200);

    foo.swap(bar);

    std::cout << "foo contains:";
    for (unsigned i = 0; i < foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i = 0; i < bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << '\n';

    return 0;
}
