#include "bmp_reader_writer.h"
#include <string>
#include <fstream>
#include <iostream>

BmpHolder::BmpHolder() : header(), dibHeader(), color_table() {
}

void Read(const std::string &input_file, BmpHolder &image) {
    std::ifstream stream(input_file, std::ios::binary);
    stream.read(reinterpret_cast<char *>(&image.header), sizeof(image.header));
    stream.read(reinterpret_cast<char *>(&image.dibHeader), sizeof(image.dibHeader));
    image.color_table.resize(image.dibHeader.ImageHeight);
    for (size_t i = 0; i < image.dibHeader.ImageHeight; ++i) {
        for (size_t j = 0; j < image.dibHeader.ImageWidth; ++j) {
            unsigned char color[3];
            stream.read(reinterpret_cast<char *>(color), 3);
            image.color_table[i].push_back({color[0] / 255., color[1] / 255., color[2] / 255.});  // NOLINT
        }
        stream.ignore((4 - (image.dibHeader.ImageWidth * 3) % 4) % 4);
    }
    if ((image.header.id >> 8) != 'M' || (image.header.id & 0xff) != 'B') {  // NOLINT
        stream.close();
        throw std::runtime_error("\n The file is not a .bmp");
    }
    stream.close();
}

void Write(const std::string &output_file, BmpHolder &image) {
    std::ofstream stream(output_file, std::ios::binary);
    stream.write(reinterpret_cast<char *>(&image.header), sizeof(image.header));
    stream.write(reinterpret_cast<char *>(&image.dibHeader), sizeof(image.dibHeader));
    for (size_t i = 0; i < image.dibHeader.ImageHeight; ++i) {
        for (size_t j = 0; j < image.dibHeader.ImageWidth; ++j) {
            unsigned char color[3] = {static_cast<unsigned char>(image.color_table[i][j].b * 255),   // NOLINT
                                      static_cast<unsigned char>(image.color_table[i][j].g * 255),   // NOLINT
                                      static_cast<unsigned char>(image.color_table[i][j].r * 255)};  // NOLINT
            stream.write(reinterpret_cast<const char *>(color), 3);
        }
        unsigned char padding[] = {0};
        stream.write(reinterpret_cast<const char *>(padding), (4 - (image.dibHeader.ImageWidth * 3) % 4) % 4);
    }
    stream.close();
}
