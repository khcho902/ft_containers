
#include <iostream>
#include "vector.hpp"
#include <vector>


int main ()
{
    
    ft::vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    

    for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;





    return 0;
}
