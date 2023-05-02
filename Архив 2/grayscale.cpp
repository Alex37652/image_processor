#include "grayscale.h"

#include <memory>

std::unique_ptr<Grayscale> Grayscale::CreateGrayscale() {
    return std::make_unique<Grayscale>();
}

void Grayscale::Apply(BmpHolder &image) const {
    for (auto &line : image.color_table) {
        for (auto &pixel : line) {
            pixel.b = pixel.b * 0.114 + pixel.g * 0.587 + pixel.r * 0.299;  // NOLINT
            pixel.g = pixel.b;
            pixel.r = pixel.b;
        }
    }
}
