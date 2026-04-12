# Sobel Vs Scharr Colab Notebook Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a separate Google Colab notebook that benchmarks Sobel vs Scharr across CPU, naive CUDA, and optimized CUDA implementations using the existing project's benchmark sizes and reporting style.

**Architecture:** Add one standalone notebook at the repo root. The notebook will write shared image I/O code plus six operator-specific executables, generate benchmark images, validate outputs within each implementation family, then produce pairwise Sobel-vs-Scharr benchmark tables and plots for CPU, naive CUDA, and optimized CUDA.

**Tech Stack:** Jupyter notebook JSON, Google Colab shell cells, C++17, CUDA, Python 3, pandas, matplotlib

---

### Task 1: Add notebook-level acceptance test

**Files:**
- Create: `colab_sobel_vs_scharr_benchmark.ipynb`

- [ ] **Step 1: Write the failing test**

Run: `test -f "colab_sobel_vs_scharr_benchmark.ipynb"`
Expected: exit code `1` because the notebook does not exist yet.

- [ ] **Step 2: Run test to verify it fails**

Run: `test -f "colab_sobel_vs_scharr_benchmark.ipynb"`
Expected: no stdout and a failing exit status.

### Task 2: Create the standalone benchmark notebook

**Files:**
- Create: `colab_sobel_vs_scharr_benchmark.ipynb`
- Reference: `colab_phase7_optimized_cuda.ipynb`
- Reference: `colab_phase7_optimized_cuda_scharr.ipynb`

- [ ] **Step 1: Add notebook scaffold**

Create a valid notebook with:

```json
{
  "cells": [],
  "metadata": {
    "kernelspec": {
      "display_name": "Python 3",
      "language": "python",
      "name": "python3"
    },
    "language_info": {
      "name": "python"
    }
  },
  "nbformat": 4,
  "nbformat_minor": 5
}
```

- [ ] **Step 2: Add notebook content**

Include cells that:

```text
1. Explain that the notebook benchmarks Sobel vs Scharr for CPU, naive CUDA, and optimized CUDA.
2. Create project directories.
3. Write shared `image_io` support code.
4. Write CPU Sobel and CPU Scharr programs.
5. Write naive CUDA Sobel and naive CUDA Scharr programs.
6. Write optimized CUDA Sobel and optimized CUDA Scharr programs.
7. Write image comparison and test-image generation helpers.
8. Compile all binaries.
9. Generate the four benchmark images.
10. Validate Sobel outputs and Scharr outputs within each implementation family.
11. Run 2 warm-up iterations and 20 measured iterations for each operator/implementation/resolution.
12. Build pandas data frames for pairwise comparisons.
13. Plot total time and kernel time comparisons.
```

- [ ] **Step 3: Verify the notebook is valid JSON**

Run: `python3 -m json.tool "colab_sobel_vs_scharr_benchmark.ipynb" >/dev/null`
Expected: exit code `0`.

### Task 3: Verify the benchmark notebook covers the required comparisons

**Files:**
- Test: `colab_sobel_vs_scharr_benchmark.ipynb`

- [ ] **Step 1: Write the failing content check**

Run:

```bash
python3 - <<'PY'
from pathlib import Path
text = Path('colab_sobel_vs_scharr_benchmark.ipynb').read_text()
required = [
    'cpu_sobel',
    'cpu_scharr',
    'sobel_naive',
    'scharr_naive',
    'sobel_optimized',
    'scharr_optimized',
    'warmup_runs = 2',
    'measured_runs = 20',
]
missing = [item for item in required if item not in text]
if missing:
    raise SystemExit('missing: ' + ', '.join(missing))
print('all required markers present')
PY
```

Expected before implementation: fail because the file is missing or incomplete.

- [ ] **Step 2: Run the content check and verify it passes**

Run the same command.
Expected: `all required markers present`.

### Task 4: Final verification

**Files:**
- Test: `colab_sobel_vs_scharr_benchmark.ipynb`

- [ ] **Step 1: Re-run JSON validation**

Run: `python3 -m json.tool "colab_sobel_vs_scharr_benchmark.ipynb" >/dev/null`
Expected: exit code `0`.

- [ ] **Step 2: Spot-check notebook structure**

Run:

```bash
python3 - <<'PY'
import json
from pathlib import Path
data = json.loads(Path('colab_sobel_vs_scharr_benchmark.ipynb').read_text())
print('cells:', len(data['cells']))
print('first cell:', data['cells'][0]['cell_type'])
PY
```

Expected: a non-zero cell count and `first cell: markdown`.
