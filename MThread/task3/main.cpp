// Multithreading in C++
// Task by Leon Ozog
//
// You are creating a program which asynchronously receives packets of data from a distant server.
// Packets arrive in an arbitrary order, time intervals and quantities.
// When a packet arrives, a callback function your_solution::callback_packets_arrived(std::vector<Packet<simulated_data>> packets) is called.
// You might recive multiple callbacks at the same time.
//
// Each packet contains a unique ID, and list of IDs of packets which it depends on and which have to be processed before it,
// for example:
// Packet 4 depends on packets 2 and 3.
// Packet 3 depends on packets 1 and 2.
// (there are no cycles in dependencies, so for example packet 1 cant depend on packet 4)
//
// After receiving a packet, you need to get its simulated_data by calling get_obj() on it,
// and then call do_work() on simulated_data and set_resoult() on simulated_data.
// do_work() takes a vector of uint64_t as an argument, which is a vector of results of do_work() of packets which it depends on.
//
// After all packets have been processed, function callback_all_pacckets_arrived will check if all packets were processed correctly.
//
// You can modify the code however you want, but only on the reciving side (so no changes in packet_menager.h).
// Try to make your solution as fast as possible, that means you should set the results of packets as soon as its possible.
// Avoid deadlocks.
// Optimal solution shouldnt take you more than 30 lines of code.

#include "packet_menager.h"
#include "packet.h"
#include "simulated_data.h"
#include "your_solution.h"

#include <iostream>
#include <unordered_map>
#include <vector>

void callback_all_pacckets_arrived(std::unordered_map<uint64_t, Packet<simulated_data>> &packets)
{
    std::cout << "callback_all_pacckets_arrived" << std::endl;

    // check if work was pefrormend correctly
    for (auto &[id, packet] : packets)
    {
        std::vector<uint64_t> depends_on_resoults;
        for (auto depends_on_id : packet.get_depends_on_ids())
        {
            depends_on_resoults.push_back(packets.find(depends_on_id)->second.get_obj()->get_resoult());
        }
        uint64_t shoud_be = packet.get_obj()->do_work(depends_on_resoults);
        if (shoud_be != packet.get_obj()->get_resoult())
        {
            std::cout << "ERROR: wrong result of obj id: " << id << " is: " << packet.get_obj()->get_resoult() << " should be: " << shoud_be << std::endl;
        }
        else
        {
            std::cout << "OK: result of obj id: " << id << " is: " << packet.get_obj()->get_resoult() << std::endl;
        }
    }
}

int main()
{
    your_solution::start();
    PacketMenager<simulated_data> packet_menager(your_solution::callback_packets_arrived, callback_all_pacckets_arrived);
    packet_menager.start();
    return 0;
}