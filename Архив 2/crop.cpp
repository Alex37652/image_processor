#include "crop.h"

Crop::Crop(const CropParams &params) : params_(params) {
}

std::unique_ptr<Crop> Crop::CreateCrop(const CropParams &params) {
    return std::make_unique<Crop>(params);
}

void Crop::Apply(BmpHolder &image) const {
    if (params_.width < image.dibHeader.ImageWidth) {
        image.dibHeader.ImageWidth = params_.width;
        for (auto &line : image.color_table) {
            line.resize(params_.width);
        }
    }
    if (params_.height < image.dibHeader.ImageHeight) {
        size_t j = 0;
        for (size_t i = image.dibHeader.ImageHeight - params_.height; i < image.dibHeader.ImageHeight; ++i) {
            image.color_table[j] = image.color_table[i];
            ++j;
        }
        image.dibHeader.ImageHeight = params_.height;
        image.color_table.resize(params_.height);
    }
    image.header.size = (image.dibHeader.ImageWidth + ((4 - (image.dibHeader.ImageWidth * 3) % 4) % 4)) *
                            image.dibHeader.ImageHeight * 3 +
                        54;                              // NOLINT
    image.dibHeader.ImageSize = image.header.size - 54;  // NOLINT
}
