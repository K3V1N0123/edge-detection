#include <iostream>

__global__ void noopKernel() {}

int main() {
    noopKernel<<<1, 1>>>();
    cudaDeviceSynchronize();
    std::cout << "CUDA scaffold ready" << std::endl;
    return 0;
}
