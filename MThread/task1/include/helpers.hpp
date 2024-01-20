#pragma once

#include <vector>
#include <iostream>
#include <syncstream>
#include <string>

#include "mergeSort.hpp"

/**
 * @brief Neatly prints a vector in a thread-safe manner
 *
 * @tparam T - typename held in the vector
 * @param vec - vector to be printed
 */
template <typename T>
void printVector(const std::vector<T> &vec)
{
    std::osyncstream safecout(std::cout);
    safecout << "[";
    for (int i = 0; i < vec.size(); i++)
    {
        safecout << vec[i];
        if (i < vec.size() - 1)
            safecout << ", ";
    }
    safecout << "]" << std::endl;
}

/**
 * @brief Fills a vector with sample data
 *
 * @param vec
 */
void fillRandomInt(std::vector<int> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i] = std::rand() % 100;
    }
}
