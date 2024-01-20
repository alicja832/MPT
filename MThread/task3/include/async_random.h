// Leon Ozog 2023
#pragma once
#include <random>

class async_random
{
private:
    std::mt19937_64 generator;

public:
    static async_random global_random;
    void init();
    void init(int64_t seed);
    std::mt19937_64 operator*();
    int64_t uniform_int(int64_t min, int64_t max);
    double uniform_float(double min, double max);
    double normal_float(double mean, double stddev);
    int64_t operator()();
    int64_t operator()(int64_t min, int64_t max);
    double operator()(const double min, const double max);
};