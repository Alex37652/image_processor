#include "sharpening.h"
#include <vector>
#include <cmath>

std::unique_ptr<Sharpening> Sharpening::CreateSharpening() {
    return std::make_unique<Sharpening>();
}

void Sharpening::Apply(BmpHolder &image) const {
    std::vector<std::vector<Pixel>> new_color_table = Convolution(image, 5);  // NOLINT
    for (size_t i = 0; i < image.color_table.size(); ++i) {
        for (size_t j = 0; j < image.color_table[0].size(); ++j) {
            image.color_table[i][j].b = std::clamp(new_color_table[i][j].b, 0., 1.);
            image.color_table[i][j].g = std::clamp(new_color_table[i][j].g, 0., 1.);
            image.color_table[i][j].r = std::clamp(new_color_table[i][j].r, 0., 1.);
        }
    }
}
