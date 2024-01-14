/******************************************************************************

Testing Heterogeneous core differences

*******************************************************************************/
#include <iostream>
#include <sched.h>
#include <thread>
#include <chrono>
#include <vector>
#include <immintrin.h>
#include <iomanip>
#include <stdio.h>

#include "runners.hpp"

void print(std::string name, std::vector<std::vector<int>> times){

    //return vector
    std::vector<std::vector<double>> return_values;
    std::vector<double> lowest_vals;

    for (int i = 0; i < times.size(); i++){
            
        //get best core
        int lowest = times.at(i).at(0);
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
    std::cout << std::setw(30) << "";
    std::cout << std::left << std::setw(30) << "Int" << "          ";
    std::cout << std::left << std::setw(30) << "Float" << "          ";
    std::cout << std::left << std::setw(30) << "Vector" << "          " << std::endl;

    for(int i = 0; i < return_values.at(0).size(); i++){

        std::string name = "Core " + std::to_string(i);

        std::cout << std::setw(30) << name;
        for(int j = 0; j < return_values.size(); j++)
            std::cout << std::left << std::setw(30) << 100*return_values.at(j).at(i) << "          ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //to sort them, cluster them together based on some difference
    //threshold. May be better ways to do this
    std::vector<int> final_vals;
    std::vector<std::vector<int>> clusters;
    std::vector<std::vector<int>> clusters_idx;
    const int eps = 20;

    for (int i = 0; i < return_values.at(0).size(); i++){
        int hold = 0;
        for (int j = 0; j < return_values.size(); j++){
            hold += 100 * return_values.at(j).at(i);
        }
        final_vals.push_back(int(hold/return_values.size()));
    }

    //push first value as a center
    clusters.push_back({std::vector<int>({final_vals.at(0)})});
    clusters_idx.push_back({std::vector<int>({0})});

    //cluster
    for (int i = 1; i < final_vals.size(); i++){
        
        bool added = false;
        for(int j = 0; j < clusters.size(); j++){

            if (final_vals.at(i) > clusters.at(j).at(0) - 20 && final_vals.at(i) < clusters.at(j).at(0) + 20){
                clusters.at(j).push_back(final_vals.at(i));
                clusters_idx.at(j).push_back(i);
                added = true;
            }

        }

        //make new cluster if it doesn't fit any
        if (!added){
            clusters.push_back({std::vector<int>({final_vals.at(i)})});
            clusters_idx.push_back(std::vector<int>({i}));
        }
    }

    for (int i = 0; i < clusters_idx.size(); i++){
        std::cout << char(65 + i) << "-Cores:\n";
        for (int j = 0; j < clusters_idx.at(i).size(); j++){
            std::cout << std::left << std::setw(30) << "Core " << clusters_idx.at(i).at(j) << std::endl;
        }
    }
}

int main(){
    
    std::vector<std::vector<int>> runs;
    std::vector<int> int_runs = run_test<int>();
    runs.push_back(int_runs);

    std::vector<int> float_runs = run_test<float>();
    runs.push_back(float_runs);

    std::vector<int> vector_runs = run_test<int[1][1]>();
    runs.push_back(vector_runs);

    print("vector", runs);

    return 0;
}