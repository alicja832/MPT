#include <cmath>
#include <thread>
#pragma once
#include <chrono>
#include "helpers.hpp"
#include "mergeSort.hpp"
 //dziala!!!!
 template <typename T>
 void printz(std::vector <std::vector<T>*> zbior){
        for(auto i: zbior)
        {
            for(auto j: *(i))
                std::cout<<j<<std::endl;
            std::cout<<std::endl;
        }
         std::cout<<"Jest ok"<<std::endl;
 }
/**
 * @brief Solution
 *liczba watkow
 * @tparam T
 * @param vec
 */
template <typename T>
void parallelMergeSort(std::vector<T> &vec, int numThreads)
{
    //jesli jeden to po prostu wykonamy sortowanie
    if (numThreads <= 1) {
        mergeSort(vec);
    } else {
        //obliczamy ile elementow wektora przypadnie na jeden watek
        int elementsPerThread = std::ceil(static_cast<double>(vec.size()) / numThreads);

        std::vector <std::vector<T>*> zbior;
        std::vector <std::vector<T>*> u;
        std::vector<std::jthread> threads;
        std::vector <std::vector<T>> dane;
        dane.resize(numThreads);
        std::vector <std::vector<T>> v;
        v.resize(numThreads*numThreads);
        int i;
        int z=0;

        for (i = 0; i < numThreads; i++) {

            dane.clear();
            //tworzymy rozdzelne wektory
            int start = i * elementsPerThread;
            int end = std::min((i + 1) * elementsPerThread, static_cast<int>(vec.size()));

            //tworzymy nowe wektorki z danymi
            for(int k=start;k<end;k++)
            {
                dane[i].push_back(vec[k]);
            }
            
            zbior.push_back(&(dane[i]));

            threads.emplace_back([&dane,i]() {
                mergeSort(dane[i]);
            });
        }
        //joinujemy
        for (auto& thread : threads) {
            thread.join();
        }
    
        while(zbior.size()>1)
        {
            u.clear();
            for (int i = 0; i < zbior.size(); i+=2){
                 
                if((i+1)<zbior.size())
                {
                    v[z].resize(2*(*zbior[i]).size());
                    merge(v[z],*(zbior[i]),*(zbior[i+1]));
                }
                else
                {
                    v[z] = *zbior[i];
                }
                u.push_back(&(v[z])); 
                z++; 
            }
            zbior=u;    
        }
        vec=*zbior[0];
        
    }
    //na pewno bedzie inicjowanie wektora
    
}
