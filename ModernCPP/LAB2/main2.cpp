// Implement a generic function called findMaximum that finds the maximum element in a container.
// The function should work with various container types, such as arrays, vectors, and sets. 
// Use the Concepts library to ensure that the container type passed to the function supports iteration and comparison of elements.
#include <iostream>
#include <vector>
#include <concepts>
#include <array>
#include <set>
#include <algorithm>
#include <iterator>

template <typename U>
concept Cos = requires (U cont)
{
   cont.begin();

};

template <Cos T>
auto findMaximum(T u){

    auto x=*(u.begin());
    for(auto i:u)
    {
        if((i)>(x))
        {
            x=i;
        }
    }
    return x;
}


int main()
{
    std::vector<int> vectorContainer = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "Maximum in vector: " << findMaximum(vectorContainer) << std::endl;

    std::array<double, 4> arrayContainer = {2.5, 1.7, 3.2, 4.8};
    std::cout << "Maximum in array: " << findMaximum(arrayContainer) << std::endl;

    std::set<int> setContainer = {10, 5, 8, 2, 7};
    std::cout << "Maximum in set: " << findMaximum(setContainer) << std::endl;
    
}

// Maximum in vector: 9
// Maximum in array: 4.8
// Maximum in set: 10