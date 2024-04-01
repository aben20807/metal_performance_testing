#!/bin/bash
for i in {1..20}
do
    echo "iter: ${i}" >> batch_simple1_normal_8192_logs.txt
    echo "iter: ${i}" >> sep_simple1_normal_8192_logs.txt
    ./build/Release/metal_performance_testing_batch >> batch_simple1_normal_8192_logs.txt
    ./build/Release/metal_performance_testing_sep >> sep_simple1_normal_8192_logs.txt
done