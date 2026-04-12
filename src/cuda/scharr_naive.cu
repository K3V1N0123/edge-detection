#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>

#include <cuda_runtime.h>

#include "image_io.hpp"

namespace {

__global__ void scharrNaiveKernel(const std::uint8_t* input, std::uint8_t* output, int width, int height) {
    const int x = blockIdx.x * blockDim.x + threadIdx.x;
    const int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= width || y >= height) {
        return;
    }

    const int index = y * width + x;
    if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
        output[index] = 0;
        return;
    }

    const int gx =
        -3 * input[(y - 1) * width + (x - 1)] + 3 * input[(y - 1) * width + (x + 1)] +
        -10 * input[y * width + (x - 1)] + 10 * input[y * width + (x + 1)] +
        -3 * input[(y + 1) * width + (x - 1)] + 3 * input[(y + 1) * width + (x + 1)];

    const int gy =
        -3 * input[(y - 1) * width + (x - 1)] - 10 * input[(y - 1) * width + x] - 3 * input[(y - 1) * width + (x + 1)] +
        3 * input[(y + 1) * width + (x - 1)] + 10 * input[(y + 1) * width + x] + 3 * input[(y + 1) * width + (x + 1)];

    const int magnitude = min(255, abs(gx) + abs(gy));
    output[index] = static_cast<std::uint8_t>(magnitude);
}

void checkCuda(cudaError_t error, const char* step) {
    if (error != cudaSuccess) {
        throw std::runtime_error(std::string(step) + ": " + cudaGetErrorString(error));
    }
}

void printUsage(const char* program_name) {
    std::cout
        << "Usage:\n"
        << "  " << program_name << " <input.pgm> <output.pgm>\n";
}

}  // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            printUsage(argv[0]);
            return 1;
        }

        const GrayImage input = loadPgm(argv[1]);
        GrayImage output;
        output.width = input.width;
        output.height = input.height;
        output.pixels.assign(input.size(), 0);

        const std::size_t bytes = input.size() * sizeof(std::uint8_t);
        std::uint8_t* device_input = nullptr;
        std::uint8_t* device_output = nullptr;

        cudaEvent_t total_start;
        cudaEvent_t total_stop;
        cudaEvent_t kernel_start;
        cudaEvent_t kernel_stop;

        checkCuda(cudaEventCreate(&total_start), "cudaEventCreate total_start");
        checkCuda(cudaEventCreate(&total_stop), "cudaEventCreate total_stop");
        checkCuda(cudaEventCreate(&kernel_start), "cudaEventCreate kernel_start");
        checkCuda(cudaEventCreate(&kernel_stop), "cudaEventCreate kernel_stop");

        checkCuda(cudaEventRecord(total_start), "cudaEventRecord total_start");

        checkCuda(cudaMalloc(&device_input, bytes), "cudaMalloc device_input");
        checkCuda(cudaMalloc(&device_output, bytes), "cudaMalloc device_output");
        checkCuda(cudaMemcpy(device_input, input.pixels.data(), bytes, cudaMemcpyHostToDevice), "cudaMemcpy H2D");

        const dim3 block_dim(16, 16);
        const dim3 grid_dim(
            static_cast<unsigned int>((input.width + block_dim.x - 1) / block_dim.x),
            static_cast<unsigned int>((input.height + block_dim.y - 1) / block_dim.y)
        );

        checkCuda(cudaEventRecord(kernel_start), "cudaEventRecord kernel_start");
        scharrNaiveKernel<<<grid_dim, block_dim>>>(device_input, device_output, input.width, input.height);
        checkCuda(cudaGetLastError(), "scharrNaiveKernel launch");
        checkCuda(cudaEventRecord(kernel_stop), "cudaEventRecord kernel_stop");
        checkCuda(cudaEventSynchronize(kernel_stop), "cudaEventSynchronize kernel_stop");

        checkCuda(cudaMemcpy(output.pixels.data(), device_output, bytes, cudaMemcpyDeviceToHost), "cudaMemcpy D2H");
        checkCuda(cudaEventRecord(total_stop), "cudaEventRecord total_stop");
        checkCuda(cudaEventSynchronize(total_stop), "cudaEventSynchronize total_stop");

        float kernel_ms = 0.0f;
        float total_ms = 0.0f;
        checkCuda(cudaEventElapsedTime(&kernel_ms, kernel_start, kernel_stop), "cudaEventElapsedTime kernel");
        checkCuda(cudaEventElapsedTime(&total_ms, total_start, total_stop), "cudaEventElapsedTime total");

        savePgm(output, argv[2]);

        std::cout << "Naive CUDA Scharr completed" << std::endl;
        std::cout << "Input: " << argv[1] << " (" << input.width << "x" << input.height << ")" << std::endl;
        std::cout << "Output: " << argv[2] << std::endl;
        std::cout << "Kernel time: " << kernel_ms << " ms" << std::endl;
        std::cout << "Total GPU path time: " << total_ms << " ms" << std::endl;

        cudaFree(device_input);
        cudaFree(device_output);
        cudaEventDestroy(total_start);
        cudaEventDestroy(total_stop);
        cudaEventDestroy(kernel_start);
        cudaEventDestroy(kernel_stop);
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}
