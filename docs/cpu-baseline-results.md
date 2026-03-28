# CPU Baseline Performance Results

## Purpose

This document records the initial CPU-only Sobel baseline performance for the project before any CUDA implementation is introduced.

## Test Setup

- Implementation: sequential CPU Sobel filter in `src/cpu/sobel_cpu.cpp`
- Input type: generated binary grayscale PGM images
- Output type: binary grayscale PGM images
- Build mode: local CMake build
- Execution command: `./build/cpu_baseline <input.pgm> <output.pgm>`
- Timing source: internal `Timer` utility around the Sobel processing call
- Runs per case: 5

## Test Inputs

The following synthetic benchmark inputs were generated with the built-in test generator:

- `128 x 128`
- `512 x 512`
- `1280 x 720`
- `1920 x 1080`

## Results

| Resolution | Run 1 (ms) | Run 2 (ms) | Run 3 (ms) | Run 4 (ms) | Run 5 (ms) | Average (ms) |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| `128 x 128` | 1.43101 | 1.50348 | 1.70328 | 1.54238 | 1.65667 | 1.56736 |
| `512 x 512` | 24.35200 | 22.30690 | 21.82970 | 21.62140 | 21.23900 | 22.26980 |
| `1280 x 720` | 74.95000 | 84.58180 | 80.00820 | 74.31610 | 75.01720 | 77.77466 |
| `1920 x 1080` | 265.08600 | 173.89500 | 176.46700 | 174.18800 | 167.29100 | 191.38540 |

## Observations

- Runtime increases with image size as expected for a sequential Sobel implementation
- The first run for larger inputs shows some warm-up variance, especially at `1920 x 1080`
- Even with synthetic inputs, the CPU baseline provides a usable reference for later GPU speedup comparison
- These results should be treated as local-machine baseline measurements, not final benchmark results

## Notes and Limitations

- Inputs were synthetic generated patterns, not natural photographs
- Current local pipeline uses PGM images because OpenCV is not yet linked locally
- The timer currently measures the Sobel computation section only, not a full image-display pipeline
- Final reporting should distinguish local CPU timings from any Google Colab CUDA timings

## Reproduction Commands

Generate inputs:

```bash
./build/cpu_baseline --generate-test samples/images/test_128x128.pgm 128 128
./build/cpu_baseline --generate-test samples/images/test_512x512.pgm 512 512
./build/cpu_baseline --generate-test samples/images/test_1280x720.pgm 1280 720
./build/cpu_baseline --generate-test samples/images/test_1920x1080.pgm 1920 1080
```

Run the CPU baseline:

```bash
./build/cpu_baseline samples/images/test_128x128.pgm samples/images/out_128x128.pgm
./build/cpu_baseline samples/images/test_512x512.pgm samples/images/out_512x512.pgm
./build/cpu_baseline samples/images/test_1280x720.pgm samples/images/out_1280x720.pgm
./build/cpu_baseline samples/images/test_1920x1080.pgm samples/images/out_1920x1080.pgm
```
