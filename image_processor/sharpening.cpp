#include "sharpening.h"
#include <vector>
#include <cmath>

std::unique_ptr<Sharpening> Sharpening::CreateSharpening() {
    return std::make_unique<Sharpening>();
}

void Sharpening::Apply(BmpHolder &image) const {
    std::vector<std::vector<Pixel>> new_color_table(image.color_table.size(),
                                                    std::vector<Pixel>(image.color_table[0].size()));
    for (size_t i = 0; i < image.color_table.size(); ++i) {
        for (size_t j = 0; j < image.color_table[0].size(); ++j) {
            Pixel new_pixel = image.color_table[i][j] * 5;
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
            new_color_table[i][j].b = std::min(1., std::max(0., new_pixel.b));
            new_color_table[i][j].g = std::min(1., std::max(0., new_pixel.g));
            new_color_table[i][j].r = std::min(1., std::max(0., new_pixel.r));
        }
    }
    image.color_table = new_color_table;
}
