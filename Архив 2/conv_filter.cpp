//
// Created by Alex_fly on 18.03.23.
//

#include "conv_filter.h"

std::vector<std::vector<Pixel>> ConvFilter::Convolution(BmpHolder &image, int param) {
    std::vector<std::vector<Pixel>> new_color_table(image.color_table.size(),
                                                    std::vector<Pixel>(image.color_table[0].size()));
    for (size_t i = 0; i < image.color_table.size(); ++i) {
        for (size_t j = 0; j < image.color_table[0].size(); ++j) {
            Pixel new_pixel = image.color_table[i][j] * param;
            if (i > 0) {
                new_pixel -= image.color_table[i - 1][j];
            } else {
                new_pixel -= image.color_table[i][j];
            }
            if (j > 0) {
                new_pixel -= image.color_table[i][j - 1];
            } else {
                new_pixel -= image.color_table[i][j];
            }
            if (i < image.color_table.size() - 1) {
                new_pixel -= image.color_table[i + 1][j];
            } else {
                new_pixel -= image.color_table[i][j];
            }
            if (j < image.color_table[0].size() - 1) {
                new_pixel -= image.color_table[i][j + 1];
            } else {
                new_pixel -= image.color_table[i][j];
            }
            new_color_table[i][j] = new_pixel;
        }
    }
    return new_color_table;
}
