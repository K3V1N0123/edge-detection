# Phase 1: Scope Definition

## Purpose

This document captures the Phase 1 outputs from `methodology.txt`: project scope definition, implementation roadmap, and hardware/software prerequisites.

## Project Scope

### In Scope

- Sobel-based edge detection as the primary image-processing task
- CPU implementation in C++ for correctness and baseline timing
- Naive CUDA implementation for initial GPU acceleration
- Optimized CUDA implementation using shared memory and memory access improvements
- Benchmarking across CPU, naive GPU, and optimized GPU paths
- Real-time visualization for image or video streams using OpenCV
- Documentation of methodology, setup, execution, and findings

### Out of Scope

- Alternative edge detectors such as Canny, Laplacian, or deep learning methods
- Multi-GPU support
- Production deployment or packaged desktop application delivery
- Cross-platform hardware optimization beyond the chosen development setup
- Full cloud execution workflow unless needed later for CUDA access

## Problem Statement

Traditional CPU-based edge detection becomes slow for high-resolution images and real-time video streams because pixel operations are processed sequentially. This project addresses that limitation by using CUDA to parallelize Sobel filtering on the GPU and then comparing the performance and correctness of the CPU, naive GPU, and optimized GPU implementations.

## Objectives

- Build a correct CPU Sobel reference implementation
- Build a naive CUDA Sobel implementation
- Improve the CUDA path using shared memory and access optimization
- Benchmark all implementations under fixed test conditions
- Support real-time visualization using OpenCV
- Document performance gains, bottlenecks, and limitations

## Success Criteria

- CPU and GPU outputs are visually consistent
- CUDA code executes correctly on supported hardware
- Optimized CUDA outperforms the naive CUDA version
- GPU execution demonstrates measurable speedup on representative inputs
- Real-time demo shows live output with timing metrics
- Documentation is complete and reproducible

## Implementation Roadmap

### Milestone 1: Planning and Setup
- Confirm scope and required deliverables
- Document prerequisites and development constraints
- Prepare repository for implementation

### Milestone 2: CPU Baseline
- Implement Sobel filtering in C++
- Add image loading, grayscale conversion, and timing
- Generate reference outputs

### Milestone 3: Naive CUDA
- Implement one-thread-per-pixel Sobel kernel
- Transfer data between host and device
- Compare output with CPU reference

### Milestone 4: Optimized CUDA
- Introduce shared memory tiling
- Tune block and grid configuration
- Measure improvements over naive CUDA

### Milestone 5: Benchmarking
- Run tests on multiple image sizes
- Record execution time, transfer overhead, and speedup
- Summarize observations in tables or charts

### Milestone 6: Real-Time Integration
- Capture video frames using OpenCV
- Process frames using the chosen implementation path
- Display output and timing metrics live

### Milestone 7: Validation and Finalization
- Recheck correctness and runtime stability
- Finalize README, methodology, and result summaries
- Prepare for demo and submission

## Hardware and Software Prerequisites

### Minimum Development Requirements

- Operating system with C++ toolchain support
- CMake installed
- OpenCV installed and linkable from C++

### CUDA Requirements

- NVIDIA GPU with CUDA support
- Compatible NVIDIA driver
- CUDA toolkit installed
- `nvcc` available in `PATH`

### Current Constraint Note

If the working machine does not support `nvcc` or lacks compatible CUDA hardware, the project can still proceed through CPU implementation, repository setup, benchmarking design, and documentation. In this project, Google Colab will be used as the remote CUDA environment for compiling and running CUDA code when local execution is not possible.

### Execution Environment Split

- Local environment: documentation, planning, repository organization, and CPU-side development
- Google Colab: CUDA compilation, kernel execution, and GPU-side experiments

This split should be documented in benchmarking and final reporting so the execution context is clear.

## Comparison Strategy

The project will compare three paths under the same inputs and timing conditions:

- CPU baseline
- Naive CUDA
- Optimized CUDA

Each path will be validated against the CPU reference output before performance claims are accepted.

## Phase 1 Outputs Completed

- Scope definition established
- Implementation roadmap documented
- Hardware and software prerequisites documented
