# GPU-Accelerated Edge Detection with CUDA

Academic project exploring GPU parallelism for image edge detection using Sobel and Scharr operators, comparing sequential CPU, naive CUDA, and shared-memory-optimized CUDA implementations.

**Team:** Tanay Shankarikoppa, Kevin Vataliya, Kumar Harsh, Shruthi Andra  
**Guide:** Dr. Neelima B | **School:** Manipal Institute of Technology | **March 2026**

## Project Structure

| Module | Description |
|--------|-------------|
| `include/` | Core headers: `GrayImage`, `Timer`, Sobel/Scharr CPU interfaces |
| `src/cpu/` | Sequential CPU implementations (`main.cpp`, `sobel_cpu.cpp`, `scharr_cpu.cpp`) |
| `src/cuda/` | GPU kernels: naive (1 thread/pixel) and optimized (shared memory, halo loading) for both Sobel and Scharr |
| `src/common/` | Shared `image_io.cpp` (PGM P5 format) and `timer.cpp` |
| `src/tools/` | `image_compare.cpp` — pixel-level diff for correctness validation |
| `notebooks/` | Jupyter notebooks (Google Colab) for GPU experimentation |
| `benchmarks/` | `colab_naive_benchmark.py` — automated multi-run timing script |
| `docs/` | result summary |
| `samples/images/` | Test patterns (128×128 up to 1920×1080) and sample outputs |

## Algorithms

- **Sobel operator** — 3×3 kernels `Gx`, `Gy` with coefficients `[1, 2, 1]` / `[−1, 0, 1]`
- **Scharr operator** — 3×3 kernels with coefficients `[3, 10, 3]` / `[−3, 0, 3]` for improved rotational symmetry

## Implementation Variants

| Variant | Description |
|---------|-------------|
| **CPU Baseline** | Sequential C++ convolution (correctness reference) |
| **Naive CUDA** | One GPU thread per pixel, global memory reads |
| **Optimized CUDA** | Shared memory tiles with halo loading for coalesced access, boundary clamping |



## Prerequisites

- C++17 compiler (Clang, GCC, MSVC)
- CMake 3.18+
- OpenCV (optional — enables extended I/O; PGM-only mode works without it)
- NVIDIA CUDA Toolkit + `nvcc` (optional — for GPU targets)

## Build

```bash
# CPU baseline + tools only
cmake -B build && cmake --build build

# With CUDA targets
cmake -B build-cuda -DEDGE_DETECTION_ENABLE_CUDA=ON && cmake --build build-cuda

# Disable OpenCV (pure PGM mode)
cmake -B build -DEDGE_DETECTION_ENABLE_OPENCV=OFF
```

## Usage

```bash
# Generate a test pattern
./cpu_baseline --generate-test input.pgm [width height]

# Apply edge detection (default: Sobel)
./cpu_baseline input.pgm output.pgm
./cpu_baseline --algorithm scharr input.pgm output.pgm

# Compare two outputs pixel-by-pixel
./compare_images reference.pgm candidate.pgm

# CUDA variants
./cuda_naive input.pgm output.pgm
./cuda_optimized input.pgm output.pgm
```

## GPU Development (Google Colab)

Notebooks in `notebooks/` provide end-to-end GPU development:
- `sobel.ipynb` — Sobel operator: CPU, naive CUDA, optimized CUDA
- `scharr.ipynb` — Scharr operator: CPU, naive CUDA, optimized CUDA
- `scharr_vs_sobel.ipynb` — Quality comparison of both operators
