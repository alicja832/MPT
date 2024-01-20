// Leon Ozog 2023
#include "async_random.h"
#include <time.h>
#include <thread>

async_random async_random::global_random;

void async_random::init()
{
    generator = std::mt19937_64((int64_t)std::time(nullptr) + (uint64_t)(std::hash<std::thread::id>{}(std::this_thread::get_id())));
}

void async_random::init(int64_t seed)
{
    generator = std::mt19937_64(seed);
}

std::mt19937_64 async_random::operator*()
{
    return generator;
}

int64_t async_random::uniform_int(int64_t min, int64_t max)
{
    std::uniform_int_distribution<int64_t> distribution(min, max);
    return distribution(generator);
}

double async_random::uniform_float(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

double async_random::normal_float(double mean, double stddev)
{
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}

int64_t async_random::operator()()
{
    return generator();
}

int64_t async_random::operator()(const int64_t min, const int64_t max)
{
    return uniform_int(min, max);
}

double async_random::operator()(const double min, const double max)
{
    return uniform_float(min, max);
}