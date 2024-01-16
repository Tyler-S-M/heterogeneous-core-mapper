/******************************************************************************

Testing Heterogeneous core differences

*******************************************************************************/
#include <iostream>
#include <sched.h>
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <numeric>
#include <algorithm> 

#include "mapping_module.hpp"

int main(){

    class core_mapper::core_mapping core_hierarchy = core_mapper::map_core_topology(true);

    std::cout << "A-Cores:" << std::endl;
    for(int i = 0 ; i < core_hierarchy.A_cores.get_cores().size(); i++){
        std::cout << std::left << std::setw(30) << "Core " << core_hierarchy.A_cores.get_cores().at(i) << std::endl;
    }
    std::cout << "B-Cores:" << std::endl;
    for(int i = 0 ; i < core_hierarchy.B_cores.get_cores().size(); i++){
        std::cout << std::left << std::setw(30) << "Core " << core_hierarchy.B_cores.get_cores().at(i) << std::endl;
    }

    return 0;
}