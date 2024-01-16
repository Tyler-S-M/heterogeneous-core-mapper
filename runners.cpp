#include "runners.hpp"

namespace core_mapper {
    
    cpu_set_t assignToThisCore(int core_id, cpu_set_t mask){
            CPU_ZERO(&mask);
            CPU_SET(core_id, &mask);
            sched_setaffinity(0, sizeof(mask), &mask);
            return mask;
        }
}