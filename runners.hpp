#ifndef RUNNERS_HPP
#define RUNNERS_HPP

#include <iostream>
#include <sched.h>
#include <thread>
#include <chrono>
#include <vector>
#include <immintrin.h>
#include <stdio.h>

#include "tests.hpp"

using namespace std::chrono;

cpu_set_t  mask;

void assignToThisCore(int core_id){
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
}

double maxValue(const std::vector<int>& vec){
    int val_max = vec[0]; // What could go wrong on this line?
    int max_idx;

    for (int i = 0; i < vec.size(); ++i){
        if (val_max < vec[i]){
            val_max = vec[i];
            max_idx = i;
        }
    }
    return max_idx;
}

template <typename T>
std::vector<int> run_test(){

    T V;
    int Z[1][1];
    std::string name = "";

    __m256i hello;
    int a[N][N];
    int b[N][N];
    int c[N][N];

    //get all the cores
    const auto processor_count = std::thread::hardware_concurrency();
    
    std::vector<int> times;

    if (std::is_same_v<decltype(V), decltype(Z)>){

        //reset vecs
        for (int x = 0; x < N; x++){
            for (int y = 0; y < N; y++){
                a[x][y] = x+y;
                b[x][y] = x*y;
                c[x][y] = 0;
            }
        }
    }
    
    //test each core
    for(int i = 0; i < processor_count; i++){
        assignToThisCore(i);

        std::vector<int> local_times;
        int real_time = 0;

        for (int k = 0; k < 10; k++){

            auto start = high_resolution_clock::now();

            if (std::is_same_v<decltype(V), decltype(1)>){
                do_int_calc();
            }
            else if (std::is_same_v<decltype(V), decltype(float(1.0))>){
                do_floating_calc();
            }
            else{
                do_matrix_calc(a, b, c);
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);

            local_times.push_back(duration.count());

        }

        //remove worst
        int ignore = maxValue(local_times);

        //average
        for (int k = 0; k < local_times.size(); k++){
            if(k != ignore)
                real_time += local_times[k];
        }

        times.push_back(real_time/5);
    }

    return times;

}

#endif