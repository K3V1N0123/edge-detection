# CPU vs Naive GPU Results

This document compares the local CPU Sobel baseline with the naive CUDA implementation run in Google Colab.

## Current Status

- CPU baseline measurements are complete in `docs/cpu-baseline-results.md`
- Naive CUDA timings have been collected in Google Colab for the same four sample sizes
- The results below use six GPU runs, with Run 1 treated as warm-up and Runs 2-6 averaged as steady-state measurements

## CPU Reference

| Resolution | CPU Avg (ms) |
| --- | ---: |
| `128 x 128` | 1.56736 |
| `512 x 512` | 22.26980 |
| `1280 x 720` | 77.77466 |
| `1920 x 1080` | 191.38540 |

## Google Colab Naive CUDA Data

The following raw runs were collected for the same input order used in the notebook:

- `128 x 128`
- `512 x 512`
- `1280 x 720`
- `1920 x 1080`

Run 1:

- `128 x 128`: kernel `0.186048 ms`, total `0.383136 ms`
- `512 x 512`: kernel `0.153760 ms`, total `0.507232 ms`
- `1280 x 720`: kernel `0.109216 ms`, total `0.813600 ms`
- `1920 x 1080`: kernel `0.147392 ms`, total `1.609570 ms`

Run 2:

- `128 x 128`: kernel `0.171936 ms`, total `0.345184 ms`
- `512 x 512`: kernel `0.144384 ms`, total `0.488672 ms`
- `1280 x 720`: kernel `0.189184 ms`, total `1.059070 ms`
- `1920 x 1080`: kernel `0.191776 ms`, total `1.685540 ms`

Run 3:

- `128 x 128`: kernel `0.190432 ms`, total `0.377184 ms`
- `512 x 512`: kernel `0.149056 ms`, total `0.471936 ms`
- `1280 x 720`: kernel `0.127040 ms`, total `0.881792 ms`
- `1920 x 1080`: kernel `0.165856 ms`, total `1.694400 ms`

Run 4:

- `128 x 128`: kernel `0.179872 ms`, total `0.364480 ms`
- `512 x 512`: kernel `0.141472 ms`, total `0.463936 ms`
- `1280 x 720`: kernel `0.142816 ms`, total `0.898400 ms`
- `1920 x 1080`: kernel `0.162432 ms`, total `1.686210 ms`

Run 5:

- `128 x 128`: kernel `0.202400 ms`, total `0.372800 ms`
- `512 x 512`: kernel `0.141056 ms`, total `0.462624 ms`
- `1280 x 720`: kernel `0.121408 ms`, total `0.857856 ms`
- `1920 x 1080`: kernel `0.154752 ms`, total `1.516130 ms`

Run 6:

- `128 x 128`: kernel `0.153696 ms`, total `0.365248 ms`
- `512 x 512`: kernel `0.170560 ms`, total `0.484096 ms`
- `1280 x 720`: kernel `0.165824 ms`, total `0.883232 ms`
- `1920 x 1080`: kernel `0.180768 ms`, total `1.558880 ms`

## Final Comparison Table

The following table uses Runs 2-6 as the average, treating Run 1 as warm-up.

| Resolution | CPU Avg (ms) | Naive GPU Kernel Avg (ms) | Naive GPU Total Avg (ms) | Speedup vs CPU (kernel) | Speedup vs CPU (total) |
| --- | ---: | ---: | ---: | ---: | ---: |
| `128 x 128` | 1.56736 | 0.17967 | 0.36498 | 8.72x | 4.29x |
| `512 x 512` | 22.26980 | 0.14931 | 0.47425 | 149.16x | 46.95x |
| `1280 x 720` | 77.77466 | 0.14925 | 0.91607 | 521.09x | 84.90x |
| `1920 x 1080` | 191.38540 | 0.17112 | 1.62823 | 1118.97x | 117.54x |

## Interpretation

- The naive CUDA implementation is already substantially faster than the local CPU baseline, even before shared-memory optimization
- Kernel-only times are extremely small across all image sizes, showing that the Sobel computation itself maps well to GPU parallelism
- Total GPU path time is higher than kernel time because it includes host-device transfer and runtime overhead
- The gap between kernel time and total time is especially important for smaller inputs, where transfer overhead reduces effective end-to-end speedup
- These results provide a strong baseline for Phase 7, where the goal is to reduce memory overhead further and improve the CUDA path beyond the naive implementation

## Reproducibility Note

For future reruns in Google Colab, the project includes:

- `colab_phase6_naive_cuda.ipynb`
- `benchmarks/colab_naive_benchmark.py`
