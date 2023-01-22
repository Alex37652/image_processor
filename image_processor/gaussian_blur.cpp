#include "gaussian_blur.h"
#include <map>
#include <math.h>

GaussianBlur::GaussianBlur(const BlurParams &params) : params_(params) {

}

std::unique_ptr<GaussianBlur> GaussianBlur::CreateGaussianBlur(const BlurParams &params) {
    return std::make_unique<GaussianBlur>(params);
}

void GaussianBlur::Apply(BmpHolder &image) const {
    std::vector<std::vector<Pixel>> temp = image.color_table;
    int accuracy = std::ceil(3 * params_.sigma);
    std::map<int, double> koef;
    for (int k = -accuracy; k <= accuracy; ++k) {
        koef[k] = (1. / (std::sqrt(2. * M_PI) * params_.sigma)) *
                  exp(-1. * static_cast<double>(k * k) / (2 * params_.sigma * params_.sigma));
    }

    for (size_t i = 0; i < image.dibHeader.ImageHeight; ++i) {
        for (size_t j = 0; j < image.dibHeader.ImageWidth; ++j) {
            Pixel new_pixel;
            for (int k = -accuracy; k <= accuracy; ++k) {
                if (static_cast<int64_t>(j) + k >= 0 && j + k < image.dibHeader.ImageWidth) {
                    new_pixel += image.color_table[i][j + k] * koef[k];
                } else if (static_cast<int64_t>(j) + k < 0) {
                    new_pixel += image.color_table[i][0] * koef[k];
                } else {
                    new_pixel += image.color_table[i][image.dibHeader.ImageWidth - 1] * koef[k];
                }
            }
            temp[i][j] = new_pixel;
        }
    }
    for (size_t i = 0; i < image.dibHeader.ImageHeight; i++) {
        for (size_t j = 0; j < image.dibHeader.ImageWidth; j++) {
            Pixel new_pixel;
            for (int k = -accuracy; k <= accuracy; ++k) {
                if (static_cast<int64_t>(i) + k >= 0 && k + i < image.dibHeader.ImageHeight) {
                    new_pixel += temp[k + i][j] * koef[k];
                } else if (static_cast<int64_t>(j) + k < 0) {
                    new_pixel += temp[0][j] * koef[k];
                } else {
                    new_pixel += temp[image.dibHeader.ImageHeight - 1][j] * koef[k];
                }

            }
            image.color_table[i][j] = new_pixel;
        }
    }
}
