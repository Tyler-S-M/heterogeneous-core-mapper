#ifndef MAPPING_MODULE_HPP
#define MAPPING_MODULE_HPP

#include <iostream>
#include <sched.h>
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <numeric>
#include <algorithm> 

#if defined(__x86_64__) || defined(_M_X64)
    #include <immintrin.h>
#elif defined(__aarch64__) || defined(_M_ARM64)
    #include <arm_neon.h>
#endif

#include "runners.hpp"
#include "mapping_structure.hpp"

namespace core_mapper {

    double maxValue(const std::vector<int>& v);

    float average_performance(const std::vector<int>& targets, const std::vector<double>& v);

    std::vector<int> sort_indexes(const std::vector<std::vector<int>> &v);

    class core_mapping map_core_topology(bool log = false);

}

#endif