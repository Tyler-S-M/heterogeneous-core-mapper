#include "mapping_module.hpp"

namespace core_mapper {

    double maxValue(const std::vector<int>& v){
        int val_max = v[0];
        int max_idx;

        for (int i = 0; i < v.size(); i++){
            if (val_max < v[i]){
                val_max = v[i];
                max_idx = i;
            }
        }
        return max_idx;
    }

    float average_performance(const std::vector<int>& targets, const std::vector<double>& v){
        float average = 0.0;

        for(int i = 0; i < targets.size(); i++)
            average += v.at(targets.at(i));

        return average/targets.size();

    }

    std::vector<int> sort_indexes(const std::vector<std::vector<int>> &v) {

        std::vector<int> idx(v.size());
        std::vector<int> idx_indices(v.size());

        for (int i = 0; i < v.size(); i++){
            idx.at(i) = maxValue(v.at(i));
            idx_indices.at(i) = i;
        }

        //FIXME: This is really... really.... really stupid
        for(int j = 0 ; j < idx.size(); j++){
            for(int i = 0 ; i < idx.size()-1; i++){
                if (idx.at(i) < idx.at(i + 1)){
                    int store = idx.at(i);
                    int store_idx = idx_indices.at(i);
                    idx.at(i) = idx.at(i+1);
                    idx_indices.at(i) = idx.at(i+1);
                    idx.at(i+1) = store;
                    idx_indices.at(i) = store_idx;
                }
            }
        }

    return idx_indices;
    }

    class core_mapping map_core_topology(bool log){

        //run the tests
        std::vector<std::vector<int>> times;
        std::vector<int> int_runs = run_test<int>();
        times.push_back(int_runs);

        std::vector<int> float_runs = run_test<float>();
        times.push_back(float_runs);

        std::vector<int> vector_runs = run_test<int[1][1]>();
        times.push_back(vector_runs);

        //holding vectors
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

        if (log){
            std::cout << "Individual core performance in relation to the fastest core in each test:\n";
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
        }

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

                if (final_vals.at(i) > clusters.at(j).at(0) - eps && final_vals.at(i) < clusters.at(j).at(0) + eps){
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

        std::vector<int> topology_sorted = sort_indexes(clusters_idx);

        //make a core mapping object to return
        if (topology_sorted.size() == 3)
            return core_mapping(
                                clusters_idx.at(topology_sorted.at(0)), 
                                average_performance(clusters_idx.at(topology_sorted.at(0)), return_values.at(0)), 
                                average_performance(clusters_idx.at(topology_sorted.at(0)), return_values.at(1)), 
                                average_performance(clusters_idx.at(topology_sorted.at(0)), return_values.at(2)),
                                clusters_idx.at(topology_sorted.at(1)), 
                                average_performance(clusters_idx.at(topology_sorted.at(1)), return_values.at(0)), 
                                average_performance(clusters_idx.at(topology_sorted.at(1)), return_values.at(1)), 
                                average_performance(clusters_idx.at(topology_sorted.at(1)), return_values.at(2)),
                                clusters_idx.at(topology_sorted.at(2)), 
                                average_performance(clusters_idx.at(topology_sorted.at(2)), return_values.at(0)), 
                                average_performance(clusters_idx.at(topology_sorted.at(2)), return_values.at(1)), 
                                average_performance(clusters_idx.at(topology_sorted.at(2)), return_values.at(2))
                                );
        if (topology_sorted.size() == 2)
            return core_mapping(
                                clusters_idx.at(topology_sorted.at(0)), 
                                average_performance(clusters_idx.at(topology_sorted.at(0)), return_values.at(0)), 
                                average_performance(clusters_idx.at(topology_sorted.at(0)), return_values.at(1)), 
                                average_performance(clusters_idx.at(topology_sorted.at(0)), return_values.at(2)),
                                clusters_idx.at(topology_sorted.at(1)), 
                                average_performance(clusters_idx.at(topology_sorted.at(1)), return_values.at(0)), 
                                average_performance(clusters_idx.at(topology_sorted.at(1)), return_values.at(1)), 
                                average_performance(clusters_idx.at(topology_sorted.at(1)), return_values.at(2))
                                );
        else
            return core_mapping(
                                clusters_idx.at(topology_sorted.at(0)), 
                                average_performance(clusters_idx.at(topology_sorted.at(0)), return_values.at(0)), 
                                average_performance(clusters_idx.at(topology_sorted.at(0)), return_values.at(1)), 
                                average_performance(clusters_idx.at(topology_sorted.at(0)), return_values.at(2))
                                );
    }

}