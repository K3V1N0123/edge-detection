# edge-detection

High-performance image processing project focused on Sobel edge detection using C++, OpenCV, and CUDA.

## Project Overview

This project compares three execution paths for edge detection:

- CPU baseline using C++
- Naive CUDA implementation using one thread per pixel
- Optimized CUDA implementation using better memory access patterns

The target outcome is a reproducible comparison of correctness and performance, followed by a real-time visualization demo for image and video inputs.

## Current Status

- Phase 1 complete: scope, roadmap, and prerequisites documented
- Phase 2 complete: repository scaffolding and starter build setup added
- Phase 3 complete: benchmark and validation plan documented
- Functional implementation not started yet

## Planned Workflow

1. Define scope, deliverables, and prerequisites
2. Set up repository structure and build system
3. Finalize benchmark requirements and validation criteria
4. Implement CPU Sobel baseline
5. Implement naive CUDA Sobel kernel
6. Optimize CUDA path with shared memory and tuning
7. Benchmark CPU vs GPU variants
8. Integrate real-time video processing with OpenCV
9. Validate outputs and finalize documentation

## Core Deliverables

- CPU Sobel implementation
- Naive CUDA Sobel implementation
- Optimized CUDA Sobel implementation
- Benchmark results across multiple input sizes
- Real-time visualization demo
- Final methodology and usage documentation

## Prerequisites

### Required

- C++ compiler with modern standard support
- OpenCV installed for image and video I/O
- CMake for build configuration

### For CUDA Phases

- NVIDIA GPU with CUDA support
- Matching NVIDIA driver and CUDA toolkit
- `nvcc` compiler available on the target machine

If local CUDA support is unavailable, the CPU baseline and project structure can still be completed locally, and CUDA phases can be run on Google Colab or another compatible remote NVIDIA environment.

## Development Setup Note

- Local machine is used for documentation, planning, and non-CUDA project work
- Google Colab is used for CUDA compilation and execution where local `nvcc` compatibility is unavailable
- CUDA benchmarking results should clearly state when they were produced in Colab instead of the local machine

## Documentation

- Project synopsis: `synopsis.txt`
- Full methodology: `methodology.txt`
- Phase 1 scope and roadmap: `docs/phase-1-scope.md`
- Phase 2 setup: `docs/phase-2-setup.md`
- Phase 3 benchmark plan: `docs/phase-3-benchmark-plan.md`
- Phase 4 system design: `docs/phase-4-system-design.md`
