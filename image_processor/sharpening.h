#pragma once

#include "factory.h"

class Sharpening : public Filter {
public:
    Sharpening() = default;

    static std::unique_ptr<Sharpening> CreateSharpening();

    void Apply(BmpHolder &image) const override;
};
