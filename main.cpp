/******************************************************************************

Testing Heterogeneous core differences

*******************************************************************************/
#include <iostream>
#include <sched.h>
#include <thread>
#include <chrono>
#include <vector>
#include <immintrin.h>
#include <stdio.h>

#include "runners.hpp"

void print(std::string name, std::vector<int> times){
    std::cout << "Time Deltas Across Heterogeneous Cores With " << name << " tests" << ":\n";
    for(int i = 0; i < times.size(); i++){
        std::cout << "Core: " << i << ": " << times.at(i) << "ns" << std::endl;
    }
}

int main(){
    
    std::vector<int> int_runs = run_test<int>();
    print("int", int_runs);

    std::vector<int> float_runs = run_test<float>();
    print("float", float_runs);

    std::vector<int> vector_runs = run_test<void*>();
    print("vector", vector_runs);

    return 0;
}