import re
import subprocess
from statistics import mean


CASES = [
    ("128 x 128", "samples/images/test_128x128.pgm", "samples/images/test_128x128_cuda_out.pgm", 1.56736),
    ("512 x 512", "samples/images/test_512x512.pgm", "samples/images/test_512x512_cuda_out.pgm", 22.26980),
    ("1280 x 720", "samples/images/test_1280x720.pgm", "samples/images/test_1280x720_cuda_out.pgm", 77.77466),
    ("1920 x 1080", "samples/images/test_1920x1080.pgm", "samples/images/test_1920x1080_cuda_out.pgm", 191.38540),
]

KERNEL_RE = re.compile(r"Kernel time: ([0-9.]+) ms")
TOTAL_RE = re.compile(r"Total GPU path time: ([0-9.]+) ms")


def run_case(input_path, output_path):
    result = subprocess.run(
        ["./sobel_naive", input_path, output_path],
        capture_output=True,
        text=True,
        check=True,
    )
    kernel_match = KERNEL_RE.search(result.stdout)
    total_match = TOTAL_RE.search(result.stdout)
    if not kernel_match or not total_match:
        raise RuntimeError(f"Failed to parse output:\n{result.stdout}\n{result.stderr}")
    return float(kernel_match.group(1)), float(total_match.group(1))


def main():
    print("Discarding first run of each case as warm-up. Averaging next 5 runs.\n")
    print("| Resolution | CPU Avg (ms) | Naive GPU Kernel Avg (ms) | Naive GPU Total Avg (ms) | Speedup vs CPU (kernel) | Speedup vs CPU (total) |")
    print("| --- | ---: | ---: | ---: | ---: | ---: |")

    for label, input_path, output_path, cpu_ms in CASES:
        warmup_kernel, warmup_total = run_case(input_path, output_path)
        kernels = []
        totals = []

        for _ in range(5):
            kernel_ms, total_ms = run_case(input_path, output_path)
            kernels.append(kernel_ms)
            totals.append(total_ms)

        kernel_avg = mean(kernels)
        total_avg = mean(totals)
        kernel_speedup = cpu_ms / kernel_avg if kernel_avg else 0.0
        total_speedup = cpu_ms / total_avg if total_avg else 0.0

        print(
            f"| `{label}` | {cpu_ms:.5f} | {kernel_avg:.5f} | {total_avg:.5f} | {kernel_speedup:.2f}x | {total_speedup:.2f}x |"
        )
        print(
            f"Warm-up `{label}`: kernel={warmup_kernel:.5f} ms, total={warmup_total:.5f} ms"
        )


if __name__ == "__main__":
    main()
