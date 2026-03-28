# Phase 7: Optimized CUDA Implementation

## Purpose

This phase adds the first optimized GPU path for Sobel edge detection. The goal is to improve on the naive CUDA implementation by reducing repeated global memory reads through shared-memory tiling while preserving the same output behavior.

## What Was Added

- `src/cuda/sobel_optimized.cu`
- shared-memory tile plus halo loading for each block
- the same border handling and magnitude formula used in CPU and naive CUDA paths
- a separate executable target named `cuda_optimized` when CUDA is enabled

## Optimization Strategy

- each thread block loads a `16 x 16` working tile
- shared memory stores the tile plus a 1-pixel halo on all sides
- neighboring pixels needed for the Sobel stencil are reused from shared memory instead of repeatedly reading global memory
- the kernel still writes one output pixel per thread to keep the comparison clean against the naive implementation

## Validation Workflow

1. Run the CPU baseline on a test image
2. Run `cuda_naive` on the same image
3. Run `cuda_optimized` on the same image
4. Compare outputs using `compare_images`
5. Benchmark kernel time and total GPU path time for naive vs optimized CUDA

## Suggested Colab Compile Commands

```bash
nvcc -O2 -I. -Iinclude src/cuda/sobel_naive.cu src/common/image_io.cpp -o sobel_naive
nvcc -O2 -I. -Iinclude src/cuda/sobel_optimized.cu src/common/image_io.cpp -o sobel_optimized
g++ -O2 -std=c++17 -Iinclude src/tools/image_compare.cpp src/common/image_io.cpp -o compare_images
```

## Suggested Validation Commands

```bash
./sobel_naive samples/images/test_512x512.pgm samples/images/test_512x512_cuda_naive.pgm
./sobel_optimized samples/images/test_512x512.pgm samples/images/test_512x512_cuda_opt.pgm
./compare_images samples/images/test_512x512_cuda_naive.pgm samples/images/test_512x512_cuda_opt.pgm
```

## Expected Outcome

- output remains identical or very close to the naive CUDA output
- kernel time should improve over the naive CUDA version
- total path time may improve less dramatically because host-device transfer overhead remains
