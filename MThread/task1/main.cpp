#include "helpers.hpp"
#include "mergeSort.hpp"
#include "task.hpp"
#include <algorithm>
#include <fstream>
#include <string>

/*
    MPT - Jakub Kawka - Task 1
    
    In this task your goal is to parallelise merge sort and analyse its scalability.

    You are free to modify main in any way you see fit
    
    What makes this algorithm special is that it is a divide and conquer algorithm.
    Because of this, and its simplicity, it is considered to be an "embarrassingly parallel" algorithm (and a good first-time MT algorithm) - by that we mean that it is very easy
    to logically split it into separate tasks for parallel processing.
    It also means that you will not need any memory synchronisation techniques to complete this assignment, just std::jthread (or thread) is enough.

    Your implementation of merge sort should include a way to limit the use of threads to a specific amount.

    After you implement the algorithm, prepare a graph describing the points below (in any way you see fit, just sending an image will suffice) and analyze how your implementation scales:
        a) as the number of cores is increased
        b) as the size of the task increases

    Attach a short interpretation of your results -- note, there are no 'perfect good results', your data may look different
    depending on your hardware and implementation

    Note -- scaling can be observed even for small problem sizes, but execution times can be very low -> counting time in microseconds will likely yield better graphs.
    Note -- calculating the same problem multiple times and presenting the average speedup yields better results to analyse

    EXTRA
    - Use perf, VTune or any other performance analysis tool to analyze your implementation

    EXTRA
    - How can you use the graphs you create to further upgrade your algorithm?

    A simple single-threaded implementation of merge sort and helper functions are included with this task so you only need to focus on MT.
    A gnuplot script is attached which was used to generate the example image.
    You can use any problem sizes in your image.

    FURTHER READING
    https://hal.science/hal-04078798/document - an article which reports on a very similar task,
     only with a much more sophisticated parallelisation of merge sort in Rust, general 
    methods used in the article are still very interesting, I highly recommend reading it in your free time.

*/

int main()
{

    std::srand(0);
    std::fstream file[5];
    double time_one[5];
    std::vector <int> nums = {1,2,3,4,5,6,7,8,9,10,11};
    std::vector<std::vector<int>> vectors;
    std::vector<int> elements;
    std::vector<int> e;
    vectors.resize(5);
    vectors[0].resize(500);
    vectors[1].resize(1500);
    vectors[2].resize(2500);
    vectors[3].resize(3500);
    vectors[4].resize(4500);
    

        for(int i=0;i<5;i++)
        {
            file[i].open("test"+std::to_string(vectors[i].size())+".dat",std::ios::out);
            fillRandomInt(vectors[i]);
            auto start = std::chrono::high_resolution_clock::now();
            parallelMergeSort(vectors[i],1);
            auto end = std::chrono::high_resolution_clock::now();
            auto time=std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
            time_one[i]=static_cast<double>(time);
        }
    for(auto j:nums)
    {
        for(int i=0;i<5;i++)
        {
            
            fillRandomInt(vectors[i]);
            //dziala no  i teraz tylko thready!!!lub azzzz
            auto start = std::chrono::high_resolution_clock::now();
            parallelMergeSort(vectors[i],j);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
            
            file[i]<<i<<"\t"<<j<<"\t"<<time_one[i]/static_cast<double>(duration)<<std::endl;//w ms
        }
    }

    //file.close();
    return 0;
}
