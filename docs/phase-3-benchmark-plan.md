# Phase 3: Requirements and Benchmark Design

## Purpose

This document defines how correctness and performance will be measured for the CPU, naive CUDA, and optimized CUDA implementations.

## Comparison Targets

- CPU Sobel baseline
- Naive CUDA Sobel implementation
- Optimized CUDA Sobel implementation

Each GPU output must be validated against the CPU reference before benchmark claims are accepted.

## Evaluation Metrics

### Functional Metrics
- Successful image load and processing
- Successful video frame processing
- Visual consistency between CPU and GPU outputs

### Performance Metrics
- Total execution time per image
- Kernel execution time for CUDA paths
- Host-to-device and device-to-host transfer overhead
- Frames per second for video processing
- Relative speedup against the CPU baseline

## Validation Rules

- CPU output serves as the correctness reference
- GPU output should match the CPU result visually and within acceptable numeric tolerance
- Border handling must be consistent across implementations
- Grayscale conversion logic must be identical or explicitly documented if different

## Benchmark Inputs

### Image Sizes
- Small: `512 x 512`
- Medium: `1280 x 720`
- Large: `1920 x 1080`

### Video Inputs
- Webcam stream if available
- One prerecorded video at `720p`
- One prerecorded video at `1080p` if hardware permits

## Benchmark Conditions

- Run each test multiple times and record average runtime
- Use the same input set across CPU and GPU paths
- Separate warm-up runs from measured runs for GPU tests
- Report both end-to-end time and kernel-only time where possible
- Record the execution environment for every reported result

## Environment Reporting

Every benchmark entry should specify:

- Execution environment: local machine or Google Colab
- CPU model if relevant
- GPU model if relevant
- Compiler/toolchain version
- OpenCV version
- CUDA version for GPU benchmarks

## Result Format

Results should be collected in a table with these fields:

- Implementation path
- Input type and resolution
- Total runtime
- Kernel runtime
- Transfer overhead
- FPS if applicable
- Speedup vs CPU
- Notes

## Acceptance Criteria for Phase Completion

- Benchmark inputs are selected and documented
- Evaluation metrics are fixed
- Validation rules are fixed
- Result reporting format is fixed

## Phase 3 Outputs Completed

- Benchmark plan defined
- Validation criteria documented
- Reporting structure established
