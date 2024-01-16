#ifndef TESTS_HPP
#define TESTS_HPP

#include <iostream>
#include <sched.h>
#include <thread>
#include <chrono>
#include <vector>
#include <stdio.h>

#if defined(__x86_64__) || defined(_M_X64)
    #include <immintrin.h>
#elif defined(__aarch64__) || defined(_M_ARM64)
    #include <arm_neon.h>
#endif

namespace core_mapper {
    #define TEST_SIZE 10000
    #define N 100

    #if defined(__x86_64__) || defined(_M_X64)
        void do_matrix_calc(int mat1[N][N], int mat2[N][N], int result[N][N]);

    #elif defined(__aarch64__) || defined(_M_ARM64)
        void do_matrix_calc(uint8_t mat1[N][N], uint8_t mat2[N][N], uint8_t result[N][N]);
    #endif

    float do_floating_calc();

    int do_int_calc();

}
#endif