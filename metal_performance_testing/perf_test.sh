#!/bin/bash
for i in {1..20}
do
    echo "iter: ${i}" >> perf_test_batch_simple1_normal_logs.txt
    echo "iter: ${i}" >> perf_test_sep_simple1_normal_logs.txt
    ./build/Release/metal_performance_testing_batch >> perf_test_batch_simple1_normal_logs.txt
    ./build/Release/metal_performance_testing_sep >> perf_test_sep_simple1_normal_logs.txt
done