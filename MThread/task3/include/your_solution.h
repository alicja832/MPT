#pragma once

#include "packet_menager.h"
#include "packet.h"
#include "simulated_data.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <mutex>

namespace your_solution
{
    // Utwórz mapę wyników, aby przechowywać wyniki pakietów.
    std::unordered_map<uint64_t, uint64_t> results;
    std::mutex results_mutex;

    void start()
    {
        // Inicjalizacja dowolnych zasobów przed rozpoczęciem programu.
    }

    void callback_packets_arrived(std::vector<Packet<simulated_data>> packets)
    {
        for (auto &packet : packets)
        {
            // Przetworzenie każdego pakietu.
            auto simulated_data = packet.get_obj();
            auto depends_on_ids = packet.get_depends_on_ids();

            // Przygotuj wektor wyników pakietów, od których zależy bieżący pakiet.
            std::vector<uint64_t> depends_on_results;
            for (auto depends_on_id : depends_on_ids)
            {
                std::lock_guard<std::mutex> lock(results_mutex);
                depends_on_results.push_back(results[depends_on_id]);
            }

            // Wywołaj do_work na danych symulacyjnych.
            uint64_t result = simulated_data->do_work(depends_on_results);

            // Ustaw wynik w mapie wyników.
            {
                std::lock_guard<std::mutex> lock(results_mutex);
                simulated_data->set_resoult(result);
            }

            // Możesz także wyświetlić informacje na temat przetworzonego pakietu.
            std::cout << "Processed packet " << packet.get_id() << " with result: " << result << std::endl;
        }
    }
} // namespace your_solution
