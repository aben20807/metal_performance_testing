```bash
./build/Release/metal_performance_testing_batch && ./build/Release/metal_performance_testing_sep
Running Experiments 1 through 3: matrix multiplication example with naive and optimized shaders.
Max buffer length: 115964116992 bytes
FYI, the thread execution wdith is: 32
FYI, the maximum allowed threads per threadgoup is: 1024
FYI, the thread execution wdith is: 32
FYI, the maximum allowed threads per threadgoup is: 1024
FYI, the thread execution wdith is: 32
FYI, the maximum allowed threads per threadgoup is: 1024
FYI, the thread execution wdith is: 32
FYI, the maximum allowed threads per threadgoup is: 1024
size of weights to be allocated: 7927234560 bytes
size of weights to be allocated: 7927234560size of weights to be allocated: 7927234560 bytes
 bytes
size of weights to be allocated: 7927234560 bytes
buffer B length: 7927234560 bytes
buffer B length: 7927234560 bytes
buffer B length: 7927234560 bytes
buffer B length: 7927234560 bytes
batch loading finished
sleep: 1000 ms
Running benchmark for Metal shader: mat_mul_optimized_nv with batch loading strategy

-------------------------
Time per call: 93825.6 microseconds
1.40815 GFLOPS
-------------------------
Running Experiments 1 through 3: matrix multiplication example with naive and optimized shaders.
Max buffer length: 115964116992 bytes
FYI, the thread execution wdith is: 32
FYI, the maximum allowed threads per threadgoup is: 1024
FYI, the thread execution wdith is: 32
FYI, the maximum allowed threads per threadgoup is: 1024
FYI, the thread execution wdith is: 32
FYI, the maximum allowed threads per threadgoup is: 1024
FYI, the thread execution wdith is: 32
FYI, the maximum allowed threads per threadgoup is: 1024
size of weights to be allocated: 30 * 264241152 = 7927234560 bytes
size of weights to be allocated: 30 * 264241152 = 7927234560 bytes
size of weights to be allocated: 30 * 264241152 = 7927234560 bytes
size of weights to be allocated: 30 * 264241152 = 7927234560 bytes
sep loading finished
sleep: 1000 ms
Running benchmark for Metal shader: mat_mul_optimized_nv with sep loading strategy

-------------------------
Time per call: 284175 microseconds
0.464927 GFLOPS
-------------------------
```
