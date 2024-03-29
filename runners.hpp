#ifndef RUNNERS_HPP
#define RUNNERS_HPP

#include <iostream>
#include <sched.h>
#include <thread>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <cstdint>

#if defined(__x86_64__) || defined(_M_X64)
    #include <immintrin.h>
#elif defined(__aarch64__) || defined(_M_ARM64)
    #include <arm_neon.h>
#endif

#include "tests.hpp"

using namespace std::chrono;

namespace core_mapper {

    cpu_set_t assignToThisCore(int core_id, cpu_set_t mask);

    template <typename T>
    std::vector<int> run_test(){

        cpu_set_t  mask;

        T V;
        int Z[1][1];
        std::string name = "";

        #if defined(__x86_64__) || defined(_M_X64)
            int a[N][N];
            int b[N][N];
            int c[N][N];

        #elif defined(__aarch64__) || defined(_M_ARM64)
            uint8_t a[N][N];
            uint8_t b[N][N];
            uint8_t c[N][N];

        #endif

        //get all the cores
        const auto processor_count = std::thread::hardware_concurrency();
        
        std::vector<int> times;

        if (std::is_same_v<decltype(V), decltype(Z)>){

            //reset vecs
            for (int x = 0; x < N; x++){
                for (int y = 0; y < N; y++){
                    a[x][y] = x+y;
                    b[x][y] = int(x/2)+int(y/4);
                    c[x][y] = 0;
                }
            }
        }
        
        //test each core
        for(int i = 0; i < processor_count; i++){
            mask = assignToThisCore(i, mask);

            std::vector<long> local_times;
            long real_time = 1000000;

            for (int k = 0; k < 50; k++){

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
                auto duration = duration_cast<microseconds>(stop - start);

                local_times.push_back(duration.count());

            }

            //remove worst
            //int ignore = maxValue(local_times);

            //average
            for (int k = 0; k < local_times.size(); k++){
                if(real_time > local_times[k])
                    real_time = local_times[k];
            }

            times.push_back(real_time);///local_times.size());
        }

        return times;

    }
}
#endif
