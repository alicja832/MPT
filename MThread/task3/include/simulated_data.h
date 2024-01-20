#pragma once
#include <cstdint>
#include "async_random.h"

class simulated_data
{
    uint64_t data;
    uint64_t resoult;

public:
    simulated_data() : resoult{0}
    {
        data = async_random::global_random();
    }

    uint64_t get_data() const
    {
        return data;
    }

    uint64_t get_resoult()
    {
        return resoult;
    }

    void set_resoult(uint64_t resoult)
    {
        this->resoult = resoult;
    }

    uint64_t do_work(std::vector<uint64_t> other_data)
    {
        uint64_t out = data;
        for (auto other : other_data)
        {
            out ^= other << 3;
        }
        return out;
    }
};
