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

void print(std::string name, std::vector<std::vector<int>> times){

    //return vector
    std::vector<std::vector<double>> return_values;
    std::vector<double> lowest_vals;

    for (int i = 0; i < times.size(); i++){
            
        //get best core
        int lowest = 10000000;
        int lowest_idx = 0;
        for (int z = 0; z < times.at(i).size(); z++){
            if (times.at(i).at(z) < lowest){
                lowest = times.at(i).at(z);
                lowest_idx = z;
            }
        }
        lowest_vals.push_back(lowest);

        //relate all other cores as percentage of that performance
        std::vector<double> hold_vec;
        for (int z = 0; z < times.at(i).size(); z++)
            hold_vec.push_back(float(lowest_vals.at(i))/float(times.at(i).at(z)));

        //add to end
        return_values.push_back(hold_vec);
    }

    std::cout << "percentage differences Deltas Across Heterogeneous Cores With " << " tests" << ":\n";
    for(int i = 0; i < return_values.size(); i++){
        for(int j = 0; j < return_values.at(i).size(); j++){
        std::cout << "Core: " << j << ": " << int(100*return_values.at(i).at(j)) << "% speed" << std::endl;
        }
    }
}

int main(){
    
    std::vector<std::vector<int>> runs;
    std::vector<int> int_runs = run_test<int>();
    runs.push_back(int_runs);

    std::vector<int> float_runs = run_test<float>();
    runs.push_back(float_runs);

    std::vector<int> vector_runs = run_test<void*>();
    runs.push_back(vector_runs);

    print("vector", runs);

    return 0;
}