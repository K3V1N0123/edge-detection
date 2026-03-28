# Results Summary

## CPU Baseline

The sequential CPU Sobel implementation established the reference output and local baseline performance:

- `128 x 128`: `1.56736 ms`
- `512 x 512`: `22.26980 ms`
- `1280 x 720`: `77.77466 ms`
- `1920 x 1080`: `191.38540 ms`

## Naive CUDA Baseline

Google Colab measurements for the naive CUDA implementation, averaged after warm-up, showed strong acceleration over the CPU baseline:

- `128 x 128`: kernel `0.17967 ms`, total `0.36498 ms`
- `512 x 512`: kernel `0.14931 ms`, total `0.47425 ms`
- `1280 x 720`: kernel `0.14925 ms`, total `0.91607 ms`
- `1920 x 1080`: kernel `0.17112 ms`, total `1.62823 ms`

## Interpretation

- even the naive CUDA version already outperforms the CPU baseline substantially
- the largest gains appear for higher resolutions, where parallel execution dominates transfer overhead
- kernel-only timings are much lower than total GPU-path timings, confirming that host-device transfer and runtime overhead remain important
- Phase 7 therefore focuses on optimizing kernel memory behavior rather than changing the surrounding transfer path first

## Recommended Reporting Angle

For the final report or presentation:

- use CPU as the correctness reference and local baseline
- use naive CUDA as the first proof of GPU acceleration
- present optimized CUDA as the stage that improves on GPU efficiency through shared-memory reuse
- discuss kernel speedup and end-to-end speedup separately
