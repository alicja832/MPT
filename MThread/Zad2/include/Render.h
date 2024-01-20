#pragma once
#include "CImg.h"
#include <vector>
#include <functional>
#include <thread>
#include <cmath>
#include <mutex>

class Render {

public:
    Render() : stopThreads(false) {}

    ~Render() {
        stopThreads = true;
        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    cimg_library::CImg<unsigned char> SwapBuffer(const cimg_library::CImg<unsigned char>& buffer, 
                                                 const std::vector<std::function<int(int, int, int)>>& animationList, 
                                                 int anim) {
        // Zainicjuj bufor do przechowywania wyników animacji
        cimg_library::CImg<unsigned char> result(buffer.width(), buffer.height(), 1, 3, 0);

        // Zastosuj wielowątkowe generowanie animacji
        threads.clear();
        for (int i = 0; i < buffer.width(); ++i) {
            threads.emplace_back(&Render::GenerateAnimationColumn, this, std::ref(result), i, std::cref(animationList), anim);
        }

        // Czekaj na zakończenie wszystkich wątków
        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        return result;
    }

private:
    // Funkcja generująca animację dla jednej kolumny
    void GenerateAnimationColumn(cimg_library::CImg<unsigned char>& result, int column, 
                                 const std::vector<std::function<int(int, int, int)>>& animationList, int anim) {
                                    
        for (int j = 0; j < result.height(); ++j) {
            if (stopThreads) return;

            // Wybierz odpowiednią funkcję animacji dla danego piksela
            int red = animationList[0](column, j, anim);
            int green = animationList[1](column, j, anim);
            int blue = animationList[2](column, j, anim);

            // Ustaw wynik w buforze
            std::lock_guard<std::mutex> lock(mutex);
            result(column, j, 0) = red;
            result(column, j, 1) = green;
            result(column, j, 2) = blue;
        }
    }

    std::vector<std::thread> threads; // Wektora przechowująca wątki
    std::mutex mutex; // Mutex do synchronizacji dostępu do bufora
    bool stopThreads; // Flaga do zatrzymywania wątków
};

