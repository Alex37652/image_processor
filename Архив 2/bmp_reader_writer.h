#pragma once

#include <vector>
#include <string>

struct Pixel {
    double b = 0;
    double g = 0;
    double r = 0;

    Pixel &operator+=(const Pixel &other) {
        b += other.b;
        g += other.g;
        r += other.r;
        return *this;
    }

    Pixel &operator-=(const Pixel &other) {
        b -= other.b;
        g -= other.g;
        r -= other.r;
        return *this;
    }

    Pixel operator*(double value) const {
        Pixel answer;
        answer.b = b * value;
        answer.g = g * value;
        answer.r = r * value;
        return answer;
    }
};

struct BmpHolder {
    BmpHolder();

    struct Header {
        uint16_t id;
        uint32_t size;
        uint32_t unused;
        uint32_t offset;
    } __attribute__((packed)) header;
    struct DIBHeader {
        uint32_t HeaderSize;
        uint32_t ImageWidth;
        uint32_t ImageHeight;
        uint16_t Planes;
        uint16_t BitsPerPixel;
        uint32_t Compression;
        uint32_t ImageSize;
        int32_t XpixelsPerMeter;
        int32_t YpixelsPerMeter;
        uint32_t TotalColors;
        uint32_t ImportantColors;
    } __attribute__((packed)) dibHeader;
    std::vector<std::vector<Pixel>> color_table;
};

void Read(const std::string &input_file, BmpHolder &image);

void Write(const std::string &output_file, BmpHolder &image);
