#include "mapping_structure.hpp"

namespace core_mapper {

    float core_structure::get_int_perf(){
        return int_perf;
    }

    float core_structure::get_float_perf(){
        return float_perf;
    }

    float core_structure::get_vec_perf(){
        return vec_perf;
    }

    std::vector<int> core_structure::get_cores(){
        return cores;
    }

    core_mapping::core_mapping(std::vector<int> in_A_Cores, float A_int_perf, float A_float_perf, float A_vec_perf,
                    std::vector<int> in_B_Cores, float B_int_perf, float B_float_perf, float B_vec_perf,
                    std::vector<int> in_C_Cores, float C_int_perf, float C_float_perf, float C_vec_perf){
                        A_cores = core_structure(in_A_Cores, A_int_perf, A_float_perf, A_vec_perf);
                        B_cores = core_structure(in_B_Cores, B_int_perf, B_float_perf, B_vec_perf);
                        C_cores = core_structure(in_C_Cores, C_int_perf, C_float_perf, C_vec_perf);
                    }

    core_mapping::core_mapping(std::vector<int> in_A_Cores, float A_int_perf, float A_float_perf, float A_vec_perf,
                    std::vector<int> in_B_Cores, float B_int_perf, float B_float_perf, float B_vec_perf){
                        A_cores = core_structure(in_A_Cores, A_int_perf, A_float_perf, A_vec_perf);
                        B_cores = core_structure(in_B_Cores, B_int_perf, B_float_perf, B_vec_perf);
                    }

    core_mapping::core_mapping(std::vector<int> in_A_Cores, float A_int_perf, float A_float_perf, float A_vec_perf){
                        A_cores = core_structure(in_A_Cores, A_int_perf, A_float_perf, A_vec_perf);
                    }

}