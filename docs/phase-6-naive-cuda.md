# Phase 6: Naive CUDA Implementation

## Purpose

This phase introduces the first GPU implementation of Sobel edge detection. The naive CUDA version is intended to establish a working CPU-vs-GPU comparison before any shared-memory optimization is added.

## What Was Added

- A real naive CUDA Sobel kernel in `src/cuda/sobel_naive.cu`
- One-thread-per-pixel GPU processing model
- PGM input/output compatibility to match the CPU baseline
- CUDA event timing for:
  - kernel time
  - total GPU path time

## Implementation Notes

- Each CUDA thread computes one output pixel
- Border pixels are set to zero, matching the CPU baseline rule
- Gradient magnitude uses `min(255, abs(gx) + abs(gy))`
- Block size is currently `16 x 16`
- This version uses direct global memory reads without shared-memory optimization

## Expected Role in the Project

- Provide the first working GPU baseline
- Expose host-device transfer overhead
- Serve as the comparison point for the optimized CUDA phase

## Google Colab Workflow

Because local `nvcc` support is unavailable, this phase is intended to run on Google Colab.

### Suggested compile command

```bash
nvcc -O2 -I. -Iinclude src/cuda/sobel_naive.cu src/common/image_io.cpp -o sobel_naive
```

### Suggested run command

```bash
./sobel_naive samples/images/test_512x512.pgm samples/images/test_512x512_cuda_out.pgm
```

## Validation Plan

- Use the same PGM inputs created for the CPU baseline
- Compare the output image visually against the CPU-generated output
- Record both kernel time and total GPU path time
- Report clearly that results were collected in Google Colab

## Planned Benchmark Comparison Fields

- input resolution
- CPU elapsed time
- naive CUDA kernel time
- naive CUDA total time
- speedup vs CPU
- execution environment

## Current Status

- Phase 6 source is prepared
- Local execution is not verified because CUDA is not available on this machine
- Verification should be performed in Google Colab next

## Supporting Files

- Colab notebook: `colab_phase6_naive_cuda.ipynb`
- Result template: `docs/cpu-vs-gpu-results-template.md`
- Rerun benchmark script: `benchmarks/colab_naive_benchmark.py`
- Comparison doc: `docs/cpu-vs-gpu-results.md`
