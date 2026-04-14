# Sobel vs Scharr Naive CUDA Benchmark - Design Spec

## Overview
Simplify the existing Colab notebook to compare only Naive CUDA implementations, and add edge detection quality metrics suitable for synthetic test patterns.

## Scope

### Comparisons
- Naive CUDA Sobel vs Naive CUDA Scharr only (remove CPU and Optimized CUDA)

### Quality Metrics (synthetic test patterns)

1. **Edge Thinness Ratio**
   - Ratio of detected edge pixels to skeletonized edge pixels
   - Lower = thinner, more accurate edges
   - Algorithm: Canny-like skeletonization via morphological operations

2. **Edge Continuity Score**
   - Percentage of edge pixels belonging to the largest connected component
   - Higher = more continuous edges, better localization

3. **Flat Region Response**
   - Mean/max gradient magnitude in known flat regions (should be ~0)
   - Lower = less noise/ringing in uniform areas

4. **Edge Strength Correlation**
   - Pearson correlation between Sobel and Scharr output magnitudes
   - Higher = similar edge detection patterns

## Implementation

### Notebook Changes
1. Remove CPU implementations (sobel_cpu, scharr_cpu)
2. Remove optimized CUDA implementations (sobel_optimized, scharr_optimized)
3. Remove Table 1 (CPU) and Table 3 (Optimized CUDA)
4. Update benchmark cell to only test naive_cuda
5. Add quality metrics computation cell
6. Add visualization comparing edge detection quality

### New Code Cell
```python
# Quality metrics for Sobel vs Scharr (Naive CUDA)
# Uses 512x512 test pattern for detailed analysis
```
