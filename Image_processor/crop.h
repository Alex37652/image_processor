#pragma once

#include "factory.h"

class Crop : public Filter {
public:
    explicit Crop(const CropParams &params);

    static std::unique_ptr<Crop> CreateCrop(const CropParams &params);

    void Apply(BmpHolder &image) const override;

private:
    CropParams params_;
};
