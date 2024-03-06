#pragma once

#include "factory.h"
#include "conv_filter.h"

class Sharpening : public ConvFilter {
public:
    Sharpening() = default;

    static std::unique_ptr<Sharpening> CreateSharpening();

    void Apply(BmpHolder &image) const override;
};
