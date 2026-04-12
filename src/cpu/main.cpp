#include <exception>
#include <iostream>
#include <string>

#include "image_io.hpp"
#include "scharr_cpu.hpp"
#include "sobel_cpu.hpp"
#include "timer.hpp"

namespace {

enum class CpuAlgorithm {
    Sobel,
    Scharr,
};

const char* toString(CpuAlgorithm algorithm) {
    return algorithm == CpuAlgorithm::Scharr ? "Scharr" : "Sobel";
}

CpuAlgorithm parseAlgorithm(const std::string& name) {
    if (name == "sobel") {
        return CpuAlgorithm::Sobel;
    }
    if (name == "scharr") {
        return CpuAlgorithm::Scharr;
    }
    throw std::runtime_error("Unsupported algorithm '" + name + "'. Expected 'sobel' or 'scharr'.");
}

void printUsage(const char* program_name) {
    std::cout
        << "Usage:\n"
        << "  " << program_name << " --generate-test <output.pgm> [width height]\n"
        << "  " << program_name << " --algorithm <sobel|scharr> <input.pgm> <output.pgm>\n"
        << "  " << program_name << " <input.pgm> <output.pgm>\n";
}

}  // namespace

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            printUsage(argv[0]);
            return 1;
        }

        if (std::string(argv[1]) == "--generate-test") {
            if (argc != 3 && argc != 5) {
                printUsage(argv[0]);
                return 1;
            }

            int width = 256;
            int height = 256;
            if (argc == 5) {
                width = std::stoi(argv[3]);
                height = std::stoi(argv[4]);
            }

            const GrayImage image = makeTestPattern(width, height);
            savePgm(image, argv[2]);
            std::cout << "Generated test image: " << argv[2] << " (" << width << "x" << height << ")" << std::endl;
            return 0;
        }

        CpuAlgorithm algorithm = CpuAlgorithm::Sobel;
        int path_arg_index = 1;

        if (std::string(argv[1]) == "--algorithm") {
            if (argc != 5) {
                printUsage(argv[0]);
                return 1;
            }
            algorithm = parseAlgorithm(argv[2]);
            path_arg_index = 3;
        } else if (argc != 3) {
            printUsage(argv[0]);
            return 1;
        }

        const GrayImage input = loadPgm(argv[path_arg_index]);

        Timer timer;
        timer.start();
        const GrayImage output = algorithm == CpuAlgorithm::Scharr
            ? applyScharrCpu(input)
            : applySobelCpu(input);
        const double elapsed_ms = timer.stopMillis();

        savePgm(output, argv[path_arg_index + 1]);

        std::cout << "CPU " << toString(algorithm) << " completed" << std::endl;
        std::cout << "Input: " << argv[path_arg_index] << " (" << input.width << "x" << input.height << ")" << std::endl;
        std::cout << "Output: " << argv[path_arg_index + 1] << std::endl;
        std::cout << "Elapsed time: " << elapsed_ms << " ms" << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}
