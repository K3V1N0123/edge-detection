#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

struct GrayImage {
    int width = 0;
    int height = 0;
    std::vector<std::uint8_t> pixels;

    bool empty() const;
    std::size_t size() const;
    std::uint8_t& at(int x, int y);
    const std::uint8_t& at(int x, int y) const;
};

GrayImage makeTestPattern(int width, int height);
GrayImage loadPgm(const std::string& path);
void savePgm(const GrayImage& image, const std::string& path);
