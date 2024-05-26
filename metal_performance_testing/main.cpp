//
//  main.cpp
//  metal_performance_testing
//
//  Created by Brian Vogel on 2022/08/27.
//

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

#include <iostream>
#include <chrono>
#include <thread>

#include "Utilities.h"
#include "MatrixMultiplier.h"

using namespace std;


float matmul_time_to_gflops(float rows, float cols, float inner_dim, float microsecs) {
    return 2e-3  * static_cast<float>(rows) * static_cast<float>(cols) * static_cast<float>(inner_dim) / static_cast<float>(microsecs);
}

void run_mat_mult() {
    // Perform matrix multiplication using custom shaders:
    // - simple custom shader with no optimization.
    // - optimized custom shader ported from existing CUDA kernel.
    //
    // Computes:
    // X <- A * B
    //
    // where the matrices are of floats and have the followqing sizes:
    //
    // X size: rows_X x cols_X
    // A size: rows_X x inner_dim
    // B size: inner_dim x cols_X
    
    const int rows_X = 1;
    const int cols_X = 6144;
    const int inner_dim = 10752;
    const int layers = 30; // batch cause bus error // 40: layers; 3: Q,K,V; 2: bf16
    const int num_of_experts = 4;
    const int sleep_ms = 1000;
    const int n_samples = 5;

    cout << "Running Experiments 1 through 3: matrix multiplication example with naive and optimized shaders." << endl;
    
    // Get the GPU device.
    MTL::Device *device = MTL::CreateSystemDefaultDevice();

    cout << "Max buffer length: " << device->maxBufferLength() << " bytes" << endl;

    // const string shader_name = "mat_mul_simple1";
    const string shader_name = "mat_mul_optimized_nv";

    std::vector<MatrixMultiplier> experts;
    for (int i = 0; i < num_of_experts; i++) {
        experts.emplace_back(device, shader_name);
    }

    std::vector<std::thread> t_init;

#ifdef LOAD_SEP
    for (auto& e: experts) {
        t_init.emplace_back([&e] {
            e.sep_allocate_memory(rows_X, cols_X, inner_dim, layers);
            e.sep_initialize_data();
        });
    }
    for(auto& t: t_init) { t.join(); }
    cout << "sep loading finished" << endl;
    
    // Warming up
    // std::vector<std::thread> t_warm;
    // for (auto& e: experts) {
    //     t_warm.emplace_back(std::thread([&e] {e.multiply_on_sep_weights_on_gpu();}));
    // }
    // for(auto& t: t_warm) { t.join(); }
    
    cout << "sleep: " << sleep_ms << " ms\n";
    float microsec_per_call;
    // Benchmark the Metal code
    
    cout << "Running benchmark for Metal shader: " << shader_name << " with sep loading strategy" << endl;
    microsec_per_call = benchmark(n_samples, [&] () {
        // Perform the multiplication
        std::vector<std::thread> t_layer;
        for (auto& e: experts) {
            t_layer.emplace_back(std::thread([&e] {e.multiply_on_sep_weights_on_gpu();}));
        }
        for(auto& t: t_layer) { t.join(); }
        if (sleep_ms > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
        }
    });
#endif
#ifdef LOAD_BATCH
    for (auto& e: experts) {
        t_init.emplace_back([&e] {
            e.batch_allocate_memory(rows_X, cols_X, inner_dim, layers);
            e.batch_initialize_data();
        });
    }
    for(auto& t: t_init) { t.join(); }
    cout << "batch loading finished" << endl;
    
    // Warming up
    // std::vector<std::thread> t_warm;
    // for (auto& e: experts) {
    //     t_warm.emplace_back(std::thread([&e] {e.multiply_on_batch_weights_on_gpu();}));
    // }
    // for(auto& t: t_warm) { t.join(); }

    cout << "sleep: " << sleep_ms << " ms\n";
    float microsec_per_call;
    // Benchmark the Metal code

    cout << "Running benchmark for Metal shader: " << shader_name << " with batch loading strategy" << endl;
    microsec_per_call = benchmark(n_samples, [&] () {
        // Perform the multiplication
        std::vector<std::thread> t_layer;
        for (auto& e: experts) {
            t_layer.emplace_back(std::thread([&e] {e.multiply_on_batch_weights_on_gpu();}));
        }
        for(auto& t: t_layer) { t.join(); }
        if (sleep_ms > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
        }
    });
#endif

    cout << "\n-------------------------\n";
    microsec_per_call -= sleep_ms * 1000.0;
    std::cout << "Time per call: " << microsec_per_call << " microseconds" << std::endl;
    cout << matmul_time_to_gflops(rows_X, cols_X, inner_dim, microsec_per_call) << " GFLOPS";
    cout << "\n-------------------------\n";
}
   

int main(void)
{
    run_mat_mult();
}
