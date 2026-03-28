#include <exception>
#include <iostream>
#include <string>

#include "image_io.hpp"
#include "sobel_cpu.hpp"
#include "timer.hpp"

namespace {

void printUsage(const char* program_name) {
    std::cout
        << "Usage:\n"
        << "  " << program_name << " --generate-test <output.pgm> [width height]\n"
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

        if (argc != 3) {
            printUsage(argv[0]);
            return 1;
        }

        const GrayImage input = loadPgm(argv[1]);

        Timer timer;
        timer.start();
        const GrayImage output = applySobelCpu(input);
        const double elapsed_ms = timer.stopMillis();

        savePgm(output, argv[2]);

        std::cout << "CPU Sobel completed" << std::endl;
        std::cout << "Input: " << argv[1] << " (" << input.width << "x" << input.height << ")" << std::endl;
        std::cout << "Output: " << argv[2] << std::endl;
        std::cout << "Elapsed time: " << elapsed_ms << " ms" << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}
