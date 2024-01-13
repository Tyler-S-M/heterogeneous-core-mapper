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

int main(){
    
    run_test<int>();

    run_test<float>();

    run_test<void*>();

    return 0;
}