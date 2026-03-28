#include "sobel_cpu.hpp"

#include <algorithm>
#include <cstdlib>

GrayImage applySobelCpu(const GrayImage& input) {
    GrayImage output;
    output.width = input.width;
    output.height = input.height;
    output.pixels.assign(input.size(), 0);

    if (input.width < 3 || input.height < 3) {
        return output;
    }

    for (int y = 1; y < input.height - 1; ++y) {
        for (int x = 1; x < input.width - 1; ++x) {
            const int gx =
                -input.at(x - 1, y - 1) + input.at(x + 1, y - 1) +
                -2 * input.at(x - 1, y) + 2 * input.at(x + 1, y) +
                -input.at(x - 1, y + 1) + input.at(x + 1, y + 1);

            const int gy =
                -input.at(x - 1, y - 1) - 2 * input.at(x, y - 1) - input.at(x + 1, y - 1) +
                input.at(x - 1, y + 1) + 2 * input.at(x, y + 1) + input.at(x + 1, y + 1);

            const int magnitude = std::min(255, std::abs(gx) + std::abs(gy));
            output.at(x, y) = static_cast<std::uint8_t>(magnitude);
        }
    }

    return output;
}
