# Results Summary

All GPU benchmarks were run on **Google Colab (Tesla T4, CUDA 13.0)** with 100 iterations per implementation per image size. CPU benchmarks were run on the same Colab environment for consistent comparison.

## Sobel Operator

### Average Kernel Times (ms)

| Size | CPU | Naive CUDA | Optimized CUDA |
|-----------|-----:|-----------:|---------------:|
| 128×128   | 0.38 | 0.17       | 0.19           |
| 512×512   | 6.02 | 0.16       | 0.17           |
| 1280×720  | 20.86 | 0.13      | 0.14           |
| 1920×1080 | 47.19 | 0.15       | 0.17           |

### Average Total Path Times (ms)

| Size | CPU | Naive CUDA | Optimized CUDA |
|-----------|-----:|-----------:|---------------:|
| 128×128   | 0.53 | 0.36       | 0.38           |
| 512×512   | 6.54 | 0.52       | 0.52           |
| 1280×720  | 22.35 | 0.89      | 0.89           |
| 1920×1080 | 50.53 | 1.58       | 1.61           |

### Speedup vs CPU (Total Path)

| Size | Naive CUDA | Optimized CUDA |
|-----------|-----------:|---------------:|
| 128×128   | 1.46×      | 1.40×          |
| 512×512   | 12.69×     | 12.57×         |
| 1280×720  | 25.19×     | 24.98×         |
| 1920×1080 | 31.94×     | 31.45×         |

## Scharr Operator

### Average Kernel Times (ms)

| Size | CPU | Naive CUDA | Optimized CUDA |
|-----------|-----:|-----------:|---------------:|
| 128×128   | 0.36 | 0.17       | 0.19           |
| 512×512   | 5.75 | 0.16       | 0.18           |
| 1280×720  | 19.78 | 0.12      | 0.16           |
| 1920×1080 | 45.40 | 0.15       | 0.21           |

### Average Total Path Times (ms)

| Size | CPU | Naive CUDA | Optimized CUDA |
|-----------|-----:|-----------:|---------------:|
| 128×128   | 0.51 | 0.36       | 0.37           |
| 512×512   | 6.24 | 0.50       | 0.52           |
| 1280×720  | 21.24 | 0.86      | 0.90           |
| 1920×1080 | 49.66 | 1.57       | 1.62           |

### Speedup vs CPU (Total Path)

| Size | Naive CUDA | Optimized CUDA |
|-----------|-----------:|---------------:|
| 128×128   | 1.42×      | 1.37×          |
| 512×512   | 12.45×     | 11.90×         |
| 1280×720  | 24.69×     | 23.61×         |
| 1920×1080 | 31.69×     | 30.56×         |

## Sobel vs Scharr Comparison

Scharr consistently showed marginally lower kernel times than Sobel across most sizes:

| Size | Kernel Ratio (Scharr/Sobel) | Total Ratio (Scharr/Sobel) | Winner |
|-----------|---------------------------:|--------------------------:|--------|
| 128×128   | 0.916                      | 0.931                     | Scharr |
| 512×512   | 0.895                      | 0.950                     | Scharr |
| 1280×720  | 0.914                      | 0.995                     | Scharr |
| 1920×1080 | 1.068                      | 1.018                     | Sobel  |

Overall average: Scharr is ~5% faster on kernel time across all sizes.

## Quality Metrics

| Metric | Sobel | Scharr | Winner |
|--------|------:|------:|--------|
| Thinness ratio (lower=thinner) | 1.92 | 1.44 | Scharr |
| Continuity score (higher=better) | 0.33 | 0.23 | Sobel |
| Flat region response (lower=better) | 0.015 | 0.007 | Scharr |
| Edge pixels (lower=more selective) | 2284 | 1381 | Scharr |
| Num components (lower=better continuity) | 56.0 | 50.8 | Scharr |

## Key Findings

- **Naive CUDA outperforms Optimized CUDA** for both Sobel and Scharr — the optimized kernel's shared memory halo-loading overhead outweighs benefits for small 3×3 convolutions. Naive CUDA kernel is ~9% faster for Sobel and ~16% faster for Scharr across all sizes.
- **GPU acceleration scales with resolution** — speedup plateaus at ~32× total path improvement for 1080p for both operators.
- **Host-device transfer dominates** — kernel times are typically <0.2 ms even at 1080p, while total GPU path is 1.5-1.6 ms. Reducing transfer overhead would provide larger gains than kernel optimization.
- **Scharr vs Sobel is a tradeoff** — Scharr has better flat region response (less noise) and produces fewer edge pixels (more selective), while Sobel produces thinner edges with better continuity.
