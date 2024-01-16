#include "tests.hpp"

namespace core_mapper {

    #if defined(__x86_64__) || defined(_M_X64)
        void do_matrix_calc(int mat1[N][N], int mat2[N][N], int result[N][N]){
            __m256i vec_multi_res = _mm256_setzero_si256();
            __m256i vec_mat1 = _mm256_setzero_si256();
            __m256i vec_mat2 = _mm256_setzero_si256();

            int i, j, k;
            for (i = 0; i < N; i++){
                for (j = 0; j < N; ++j){
                    //Stores one element in mat1 and use it in all computations needed before proceeding
                    //Stores as vector to increase computations per cycle
                    vec_mat1 = _mm256_set1_epi32(mat1[i][j]);

                    for (k = 0; k < N; k += 8){
                        vec_mat2 = _mm256_loadu_si256((__m256i*)&mat2[j][k]);
                        vec_multi_res = _mm256_loadu_si256((__m256i*)&result[i][k]);
                        vec_multi_res = _mm256_add_epi32(vec_multi_res ,_mm256_mullo_epi32(vec_mat1, vec_mat2));
                    }
                }
            }
        }

    #elif defined(__aarch64__) || defined(_M_ARM64)
        void do_matrix_calc(uint8_t mat1[N][N], uint8_t mat2[N][N], uint8_t result[N][N]){

            //can only do 128 bit vectors..... I think....?
            //make 3 128 bit vectors
            uint8x16x3_t vec_multi_res;
            
            int i, j, k;
            for (i = 0; i < N; i++){
                for (j = 0; j < N; ++j){
                    //Stores one element in mat1 and use it in all computations needed before proceeding
                    //Stores as vector to increase computations per cycle
                    vst1q_u8(mat1[i], vec_multi_res.val[1]);

                    for (k = 0; k < N; k += 8){
                        vst1q_u8(mat2[j], vec_multi_res.val[2]);
                        vst1q_u8(result[i], vec_multi_res.val[0]);

                        //mult -> add -> store
                        vec_multi_res.val[0] = (vec_multi_res.val[1] + vec_multi_res.val[2]) * vec_multi_res.val[0];
                    }
                }
            }
        }

    #endif

    float do_floating_calc(){
        
        float j = 0.0;
        
        //just add pi a lot
        for(int i = 0; i < int(TEST_SIZE*TEST_SIZE/20); i++){
            j += 3.141592653589793238462643383279;
        }
        
        return j;
    }

    int do_int_calc(){
        
        int j = 0.0;
        
        //just add pi a lot
        for(int i = 0; i < int(TEST_SIZE*TEST_SIZE/20); i++){
            j += 3;
        }
        
        return j;
    }

}