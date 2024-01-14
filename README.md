# heterogeneous-core-mapper

Simple mapping untility which tracks the integer, floating and vector performance of cpu cores.
The purpose is to get the performance of each core relative to the fastest P-Core and report each one back.
It shows these numbers as well as clusters the averaged results to determine core type (A,B,C)

# Example Output
Intel 12900k
```
Individual core performance in relation to the fastest core in each test:
                              Int                                     Float                                   Vector                                  
Core 0                        90.0563                                 94.486                                  83.386                                  
Core 1                        95.0869                                 100                                     99.0852                                 
Core 2                        91.9373                                 90.1882                                 81.0756                                 
Core 3                        100                                     89.5085                                 98.6254                                 
Core 4                        71.5394                                 90.1947                                 50.0497                                 
Core 5                        81.5834                                 90.1284                                 89.7157                                 
Core 6                        88.0604                                 83.1863                                 85.5585                                 
Core 7                        85.5555                                 90.1414                                 98.278                                  
Core 8                        87.4731                                 84.0666                                 87.9913                                 
Core 9                        86.9833                                 90.1245                                 100                                     
Core 10                       85.9868                                 90.1895                                 71.0357                                 
Core 11                       83.1205                                 99.3493                                 98.7462                                 
Core 12                       88.8976                                 90.2051                                 79.8875                                 
Core 13                       89.1231                                 90.1271                                 99.6164                                 
Core 14                       87.9333                                 85.5242                                 54.0631                                 
Core 15                       87.3148                                 90.1466                                 88.283                                  
Core 16                       51.7814                                 66.578                                  45.7734                                 
Core 17                       51.4417                                 69.3508                                 45.8186                                 
Core 18                       51.7862                                 77.0498                                 45.8181                                 
Core 19                       33.4236                                 69.3439                                 45.8438                                 
Core 20                       51.0955                                 63.1447                                 45.2203                                 
Core 21                       34.4655                                 69.3492                                 45.3028                                 
Core 22                       51.519                                  77.0507                                 45.6283                                 
Core 23                       46.5761                                 69.35                                   45.8393                                 

A-Cores:
Core                          0
Core                          1
Core                          2
Core                          3
Core                          4
Core                          5
Core                          6
Core                          7
Core                          8
Core                          9
Core                          10
Core                          11
Core                          12
Core                          13
Core                          14
Core                          15
B-Cores:
Core                          16
Core                          17
Core                          18
Core                          19
Core                          20
Core                          21
Core                          22
Core                          23
```