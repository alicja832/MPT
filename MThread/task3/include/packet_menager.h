#pragma once
#include "packet.h"
#include "async_random.h"

#include <functional>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

template <typename T>
class PacketMenager
{
    static constexpr uint64_t n_of_packets = 1000;
    static constexpr double chance_for_packet_to_be_dependant_on_other_packet = 0.2;
    static constexpr uint64_t max_number_of_packets_packet_can_depend_on = 100;
    static constexpr uint64_t callback_threads = 4;
    static constexpr double max_time_between_callbacks = 0.0001;
    static constexpr uint64_t max_number_of_packets_which_can_arive_at_one = 4;

    std::function<void(std::vector<Packet<T>>)> callback_packets_arrived;
    std::function<void(std::unordered_map<uint64_t, Packet<T>> &)> callback_all_packets_arrived;

    std::unordered_map<uint64_t, Packet<T>> packets;
    std::unordered_map<uint64_t, Packet<T>> packets_to_arive;
    std::mutex mutex_packets;

public:
    PacketMenager(std::function<void(std::vector<Packet<T>>)> callback_packets_arrived, std::function<void(std::unordered_map<uint64_t, Packet<T>> &)> callback_all_packets_arrived)
        : callback_packets_arrived{callback_packets_arrived}, callback_all_packets_arrived{callback_all_packets_arrived}
    {
        async_random random = async_random::global_random;

        // create packets
        for (int id = 0; id < n_of_packets; ++id)
        {
            std::vector<uint64_t> depends_on;
            if (random.uniform_float(0., 1.) < chance_for_packet_to_be_dependant_on_other_packet)
            {
                int n = random.uniform_int(0, std::min(max_number_of_packets_packet_can_depend_on, packets.size()));
                std::vector<std::pair<uint64_t, Packet<T>>> depends_on_packets;
                std::sample(packets.begin(), packets.end(), std::back_inserter(depends_on_packets), n, *random);
                for (auto &[id, packet] : depends_on_packets)
                    depends_on.push_back(id);
            }
            packets.insert({id, Packet<T>(id, std::make_shared<T>(), depends_on)});
        }
        packets_to_arive = packets;
    }

    void start()
    {
        // start callback threads
        {
            std::vector<std::jthread> threads;
            for (int i = 0; i < callback_threads; ++i)
                threads.push_back(std::jthread(&PacketMenager::callback_thread, this));
        }
        callback_all_packets_arrived(packets);
    }

private:
    void callback_thread()
    {
        async_random random;
        random.init();

        while (true)
        {
            std::vector<Packet<T>> packets_arrived;
            {
                std::lock_guard<std::mutex> lock(mutex_packets);
                if (packets_to_arive.empty())
                    return;
                std::vector<std::pair<uint64_t, Packet<T>>> packets_arrived_tmp;
                std::sample(packets_to_arive.begin(), packets_to_arive.end(), std::back_inserter(packets_arrived_tmp), 
                max_number_of_packets_which_can_arive_at_one, *random);
                
                for (auto &[id, packet] : packets_arrived_tmp)
                {
                    packets_to_arive.erase(id);
                    packets_arrived.push_back(packet);
                }
            }
            callback_packets_arrived(packets_arrived);
            std::this_thread::sleep_for(std::chrono::duration<double>(random.uniform_float(0., max_time_between_callbacks)));
        }
    }
};