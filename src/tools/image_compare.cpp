#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>

#include "image_io.hpp"

namespace {

void printUsage(const char* program_name) {
    std::cout
        << "Usage:\n"
        << "  " << program_name << " <reference.pgm> <candidate.pgm>\n";
}

}  // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            printUsage(argv[0]);
            return 1;
        }

        const GrayImage reference = loadPgm(argv[1]);
        const GrayImage candidate = loadPgm(argv[2]);

        if (reference.width != candidate.width || reference.height != candidate.height) {
            std::cerr << "Error: image dimensions do not match" << std::endl;
            return 1;
        }

        std::size_t different_pixels = 0;
        int max_abs_diff = 0;
        std::uint64_t sum_abs_diff = 0;

        for (std::size_t i = 0; i < reference.pixels.size(); ++i) {
            const int diff = std::abs(static_cast<int>(reference.pixels[i]) - static_cast<int>(candidate.pixels[i]));
            if (diff != 0) {
                ++different_pixels;
            }
            if (diff > max_abs_diff) {
                max_abs_diff = diff;
            }
            sum_abs_diff += static_cast<std::uint64_t>(diff);
        }

        const double mean_abs_diff = reference.pixels.empty()
            ? 0.0
            : static_cast<double>(sum_abs_diff) / static_cast<double>(reference.pixels.size());
        const double different_ratio = reference.pixels.empty()
            ? 0.0
            : static_cast<double>(different_pixels) / static_cast<double>(reference.pixels.size());

        std::cout << "Comparison complete" << std::endl;
        std::cout << "Reference: " << argv[1] << std::endl;
        std::cout << "Candidate: " << argv[2] << std::endl;
        std::cout << "Different pixels: " << different_pixels << std::endl;
        std::cout << "Difference ratio: " << different_ratio << std::endl;
        std::cout << "Max abs diff: " << max_abs_diff << std::endl;
        std::cout << "Mean abs diff: " << mean_abs_diff << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}
