# Phase 7: Optimized CUDA Plan

## Purpose

This phase will improve the naive CUDA implementation by reducing global memory overhead and improving thread/block efficiency.

## Planned Optimization Areas

- Shared-memory tiling for Sobel neighborhoods
- Reduced redundant global memory reads
- Better memory coalescing
- Block-size tuning against actual Colab GPU hardware

## Proposed Changes

- Add `src/cuda/sobel_optimized.cu`
- Load input tiles plus halo pixels into shared memory
- Keep the same output rule and magnitude formula as CPU and naive CUDA
- Reuse the same PGM input/output path for fair comparison

## Validation Goals

- Output remains visually consistent with CPU and naive CUDA
- Kernel time improves over the naive CUDA version
- Total path time is measured separately from kernel time

## Benchmark Goal

Phase 7 should produce a three-way comparison:

- CPU baseline
- Naive CUDA
- Optimized CUDA
