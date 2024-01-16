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

    print_core_mapping(core_mapper::map_core_topology(true));

    return 0;
}