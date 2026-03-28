# CPU vs Naive GPU Results Template

Use this template after running the naive CUDA implementation in Google Colab.

## Environment

- Local CPU environment: fill in machine / compiler details
- Google Colab GPU environment: fill in GPU model, CUDA version, and runtime type
- Input type: synthetic PGM or custom PGM

## CPU Reference

Use the averages from `docs/cpu-baseline-results.md` unless you rerun locally.

## Comparison Table

| Resolution | CPU Avg (ms) | Naive GPU Kernel (ms) | Naive GPU Total (ms) | Speedup vs CPU (kernel) | Speedup vs CPU (total) | Environment Notes |
| --- | ---: | ---: | ---: | ---: | ---: | --- |
| `128 x 128` | 1.56736 |  |  |  |  |  |
| `512 x 512` | 22.26980 |  |  |  |  |  |
| `1280 x 720` | 77.77466 |  |  |  |  |  |
| `1920 x 1080` | 191.38540 |  |  |  |  |  |

## Validation Checklist

- CPU and GPU outputs use the same input image
- GPU output is visually checked against CPU output
- Kernel time and total GPU path time are both recorded
- The Colab runtime details are captured in the final report

## Interpretation Notes

- Compare kernel-only speedup and end-to-end speedup separately
- Expect transfer overhead to reduce total-path gains, especially on smaller images
- Use this table as the baseline before Phase 7 optimized CUDA work
