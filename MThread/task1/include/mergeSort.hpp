#include <cmath>
#pragma once
#include <vector>
#include "helpers.hpp"


/**
 * @brief Merge two STL vectors together into another one
 *
 * @tparam T
 * @param vec
 * @param left
 * @param right
 */
template <typename T>
void merge(std::vector<T> &vec, const std::vector<T> &left, const std::vector<T> &right)
{
    int li = 0;
    int ri = 0;
    int vi = 0;

    while (li < left.size() && ri < right.size())
    {
        if (left[li] < right[ri])
        {
            vec[vi] = left[li];
            li++;
        }
        else
        {
            vec[vi] = right[ri];
            ri++;
        }

        vi++;
    }

    while (li < left.size())
    {
        vec[vi] = left[li];
        li++;
        vi++;
    }

    while (ri < right.size())
    {
        vec[vi] = right[ri];
        ri++;
        vi++;
    }
}

/**
 * @brief Sort an array using mergesort with STL elements
 * @tparam T
 * @param vec
 */
template <typename T>
void mergeSort(std::vector<T> &vec)
{
    if (vec.size() == 1)
        return;

    int midPoint = vec.size() / 2;

    std::vector<T> left(midPoint);
    std::vector<T> right(vec.size() - midPoint);

    for (int i = 0; i < midPoint; i++)
    {
        left[i] = vec[i];
    }

    for (int i = 0; i < right.size(); i++)
    {
        right[i] = vec[midPoint + i];
    }

    // printVector(left);
    // printVector(right);

    mergeSort(left);
    mergeSort(right);

    merge(vec, left, right);

    return;
}
