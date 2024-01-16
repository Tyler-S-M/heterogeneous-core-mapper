#ifndef MAPPING_STRUCTURE_HPP
#define MAPPING_STRUCTURE_HPP

#include <vector>
#include <iostream>
#include <iomanip>

namespace core_mapper {

    class core_structure{

        private:
            std::vector<int> cores;
            float int_perf;
            float float_perf;
            float vec_perf;
            bool active;
        
        public:
            core_structure() : active(false) {}
            core_structure(std::vector<int> inCores, float inint_perf, float infloat_perf, float invec_perf) : int_perf(inint_perf), 
                                                                                                                float_perf(infloat_perf),
                                                                                                                vec_perf(invec_perf),
                                                                                                                cores(inCores),
                                                                                                                active(true) {}
            float get_int_perf();
            float get_float_perf();
            float get_vec_perf();
            bool is_active();
            std::vector<int> get_cores();

    };

    class core_mapping {

        public:    
            class core_structure A_cores;
            class core_structure B_cores;
            class core_structure C_cores;
        
        public:
            core_mapping(std::vector<int> A_Cores, float A_int_perf, float A_float_perf, float A_vec_perf,
                        std::vector<int> B_Cores, float B_int_perf, float B_float_perf, float B_vec_perf,
                        std::vector<int> C_Cores, float C_int_perf, float C_float_perf, float C_vec_perf);

            core_mapping(std::vector<int> A_Cores, float A_int_perf, float A_float_perf, float A_vec_perf,
                        std::vector<int> B_Cores, float B_int_perf, float B_float_perf, float B_vec_perf);
            
            core_mapping(std::vector<int> A_Cores, float A_int_perf, float A_float_perf, float A_vec_perf);
    };

    void print_core_mapping(core_mapping core_map);
}
#endif