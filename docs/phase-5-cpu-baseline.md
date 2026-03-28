# Phase 5: CPU Baseline Implementation

## Purpose

This document records the first working Sobel implementation for the project.

## What Was Implemented

- A grayscale image container: `GrayImage`
- Binary PGM (`P5`) image loading and saving
- A sequential Sobel edge detector in C++
- A benchmark-friendly CLI entry point for the CPU baseline
- Test-image generation for local validation without external dependencies

## Files Added

- `include/image_io.hpp`
- `include/sobel_cpu.hpp`
- `src/common/image_io.cpp`
- `src/cpu/sobel_cpu.cpp`

## Files Updated

- `src/cpu/main.cpp`
- `CMakeLists.txt`

## Current CPU Workflow

### Generate a test image

```bash
./build/cpu_baseline --generate-test samples/images/test_input.pgm 256 256
```

### Run Sobel edge detection

```bash
./build/cpu_baseline samples/images/test_input.pgm samples/images/test_output.pgm
```

## Design Notes

- The CPU implementation uses the standard 3 x 3 Sobel kernels
- Border pixels are left as zero to match the documented comparison rule
- Edge intensity is computed as `min(255, abs(gx) + abs(gy))`
- PGM support keeps the project moving even without local OpenCV installation

## Current Limitation

- Local CPU image processing is functional for grayscale PGM files only
- OpenCV-based JPG/PNG/video support can be added later when the environment is ready

## Phase 5 Outputs Completed

- Working CPU Sobel implementation
- Timing output for CPU execution
- Reference-compatible grayscale output generation
- Initial multi-image baseline results documented in `docs/cpu-baseline-results.md`
