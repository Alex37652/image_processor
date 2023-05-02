#include "negative.h"

#include <memory>

std::unique_ptr<Negative> Negative::CreateNegative() {
    return std::make_unique<Negative>();
}

void Negative::Apply(BmpHolder &image) const {
    for (auto &line : image.color_table) {
        for (auto &pixel : line) {
            pixel.b = 1 - pixel.b;
            pixel.g = 1 - pixel.g;
            pixel.r = 1 - pixel.r;
        }
    }
}
