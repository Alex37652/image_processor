#pragma once

#include "factory.h"

class GaussianBlur : public Filter {
public:
    explicit GaussianBlur(const BlurParams &params);

    static std::unique_ptr<GaussianBlur> CreateGaussianBlur(const BlurParams &params);

    void Apply(BmpHolder &image) const override;

private:
    BlurParams params_;
};
