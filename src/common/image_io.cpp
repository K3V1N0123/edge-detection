#include "image_io.hpp"

#include <cctype>
#include <fstream>
#include <stdexcept>

namespace {

std::string readToken(std::istream& input) {
    std::string token;
    char ch = '\0';

    while (input.get(ch)) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            continue;
        }
        if (ch == '#') {
            input.ignore(4096, '\n');
            continue;
        }
        token.push_back(ch);
        break;
    }

    while (input.get(ch)) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            break;
        }
        token.push_back(ch);
    }

    if (token.empty()) {
        throw std::runtime_error("Unexpected end of file while reading PGM token");
    }

    return token;
}

}  // namespace

bool GrayImage::empty() const {
    return pixels.empty() || width <= 0 || height <= 0;
}

std::size_t GrayImage::size() const {
    return pixels.size();
}

std::uint8_t& GrayImage::at(int x, int y) {
    return pixels[static_cast<std::size_t>(y * width + x)];
}

const std::uint8_t& GrayImage::at(int x, int y) const {
    return pixels[static_cast<std::size_t>(y * width + x)];
}

GrayImage makeTestPattern(int width, int height) {
    GrayImage image;
    image.width = width;
    image.height = height;
    image.pixels.resize(static_cast<std::size_t>(width * height));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::uint8_t value = static_cast<std::uint8_t>((x + y) % 256);
            if (x > width / 4 && x < (3 * width) / 4 && y > height / 4 && y < (3 * height) / 4) {
                value = 220;
            }
            image.at(x, y) = value;
        }
    }

    return image;
}

GrayImage loadPgm(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open input image: " + path);
    }

    const std::string magic = readToken(file);
    if (magic != "P5") {
        throw std::runtime_error("Only binary PGM (P5) is supported: " + path);
    }

    GrayImage image;
    image.width = std::stoi(readToken(file));
    image.height = std::stoi(readToken(file));
    const int max_value = std::stoi(readToken(file));

    if (image.width <= 0 || image.height <= 0) {
        throw std::runtime_error("Invalid image dimensions in: " + path);
    }
    if (max_value != 255) {
        throw std::runtime_error("Only 8-bit PGM files are supported: " + path);
    }

    image.pixels.resize(static_cast<std::size_t>(image.width * image.height));
    file.read(reinterpret_cast<char*>(image.pixels.data()), static_cast<std::streamsize>(image.pixels.size()));
    if (!file) {
        throw std::runtime_error("Failed to read image pixel data: " + path);
    }

    return image;
}

void savePgm(const GrayImage& image, const std::string& path) {
    if (image.empty()) {
        throw std::runtime_error("Cannot save an empty image to: " + path);
    }

    std::ofstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open output image: " + path);
    }

    file << "P5\n" << image.width << ' ' << image.height << "\n255\n";
    file.write(reinterpret_cast<const char*>(image.pixels.data()), static_cast<std::streamsize>(image.pixels.size()));

    if (!file) {
        throw std::runtime_error("Failed to write image pixel data: " + path);
    }
}
