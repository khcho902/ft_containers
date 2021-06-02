// comparing size, capacity and max_size
#include <iostream>
#include "vector.hpp"

int main()
{
    ft::vector<int> myvector;

    bool b = myvector.empty();
    std::cout << "empty: " << b << std::endl;

    // set some content in the vector:
    for (int i = 0; i < 100; i++)
        myvector.push_back(i);

    std::cout << "size: " << (int)myvector.size() << '\n';
    std::cout << "capacity: " << (int)myvector.capacity() << '\n';
    std::cout << "max_size: " << myvector.max_size() << '\n';

    b = myvector.empty();
    std::cout << "empty: " << b << std::endl;
    return 0;
}
