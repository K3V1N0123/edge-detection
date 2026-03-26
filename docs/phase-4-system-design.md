# Phase 4: System Design and Implementation Planning

## Purpose

This document defines the technical structure of the project before the full CPU and CUDA implementations begin. It describes the main modules, data flow, execution paths, and implementation decisions needed to keep CPU and GPU comparisons consistent.

## System Architecture Overview

The project is organized around three processing paths:

- CPU baseline path
- Naive CUDA path
- Optimized CUDA path

All three paths will share a common high-level workflow:

1. Load input image or video frame
2. Convert to grayscale if needed
3. Apply Sobel edge detection
4. Normalize or clamp output for display
5. Save or display the result
6. Record timing metrics

This common flow ensures that correctness and benchmark comparisons remain fair across implementations.

## Planned Modules

### Input Module

Handles image loading and video capture.

Responsibilities:
- Read images from disk
- Capture video frames using OpenCV
- Validate input dimensions and channels
- Pass frame data to the selected processing path

Planned location:
- `src/common` for shared input helpers
- `samples/images` and `samples/videos` for test assets

### Preprocessing Module

Handles grayscale conversion and any lightweight normalization needed before Sobel filtering.

Responsibilities:
- Convert color input to grayscale
- Keep preprocessing logic consistent across CPU and GPU paths
- Ensure data is in the expected format for filtering

Planned note:
- If OpenCV grayscale conversion is used, the same conversion method should be applied for both CPU and GPU comparison paths

### CPU Processing Module

Contains the sequential Sobel implementation used as the correctness reference.

Responsibilities:
- Apply Sobel kernels in the x and y directions
- Compute gradient magnitude or chosen edge intensity output
- Handle border pixels consistently
- Return a single-channel output image

Planned location:
- `src/cpu`

### CUDA Processing Module

Contains the naive and optimized GPU implementations.

Responsibilities:
- Manage device memory allocation and deallocation
- Transfer input data between host and device
- Launch Sobel kernels
- Return output data for validation and display

Submodules:
- Naive kernel implementation
- Optimized kernel implementation with shared memory

Planned location:
- `src/cuda`

### Timing and Benchmark Module

Provides consistent runtime measurement across implementations.

Responsibilities:
- Measure CPU execution time
- Measure CUDA kernel execution time
- Measure host-device transfer time where applicable
- Provide benchmark-friendly output

Planned location:
- `include/timer.hpp`
- `src/common/timer.cpp`
- `benchmarks` for dedicated runners later

### Visualization Module

Supports result display and real-time preview.

Responsibilities:
- Show original input and edge-detected output
- Overlay or print performance metrics
- Support image mode and video mode

Planned location:
- CPU app entry point in `src/cpu`
- Shared utilities in `src/common`

## Data Flow Design

### CPU Path

1. Load image or frame into host memory
2. Convert to grayscale if needed
3. Apply sequential Sobel filter
4. Generate output image in host memory
5. Display or save output
6. Record total execution time

### Naive CUDA Path

1. Load image or frame into host memory
2. Convert to grayscale if needed
3. Copy input to device memory
4. Launch naive Sobel kernel with one thread per pixel
5. Copy result back to host memory
6. Display or save output
7. Record transfer and kernel timing

### Optimized CUDA Path

1. Load image or frame into host memory
2. Convert to grayscale if needed
3. Copy input to device memory
4. Launch optimized Sobel kernel using shared memory tiling
5. Copy result back to host memory
6. Display or save output
7. Record transfer and kernel timing

## Interface Strategy

To keep the design clean, each processing path should expose a similar interface. A simple target interface is:

- input: grayscale image buffer and image dimensions
- output: processed edge image buffer
- metadata: timing information and path identifier

This will allow the benchmark and visualization logic to reuse the same surrounding code regardless of whether the processing is done on CPU or GPU.

## Implementation Decisions

### Sobel Operator

The project will use the standard 3 x 3 Sobel kernels for horizontal and vertical gradient calculation.

### Border Handling

Border pixels will use a fixed, documented rule so that CPU and GPU outputs stay comparable. The recommended approach is to skip the outermost border and set border output pixels to zero.

### Output Format

The initial implementation should output an 8-bit single-channel edge image suitable for display with OpenCV.

### Gradient Magnitude

The recommended first implementation computes edge intensity using:

- `magnitude = min(255, abs(gx) + abs(gy))`

This is simpler than Euclidean magnitude and is commonly used for fast Sobel implementations. If a different magnitude rule is used later, it should be documented and applied consistently across all paths.

## File-Level Plan

### Existing Scaffold

- `src/cpu/main.cpp` for CPU application entry point
- `src/cuda/naive_stub.cu` for CUDA target scaffold
- `src/common/timer.cpp` and `include/timer.hpp` for timing utility

### Next Planned Files

- `include/sobel_cpu.hpp`
- `src/cpu/sobel_cpu.cpp`
- `include/image_io.hpp`
- `src/common/image_io.cpp`
- `src/cuda/sobel_naive.cu`
- `src/cuda/sobel_optimized.cu`
- `benchmarks/benchmark_plan.md` or benchmark runner source later

## Dependency Plan

### Local Machine

- CMake
- C++ compiler
- OpenCV for image I/O and display

### Google Colab

- CUDA toolkit
- `nvcc`
- NVIDIA runtime
- Optional OpenCV setup if CUDA testing extends to image-based pipeline work

## Phase 4 Outputs Completed

- Technical design outline defined
- Module boundaries identified
- Data flow for CPU and CUDA paths documented
- Initial file-level implementation plan defined
