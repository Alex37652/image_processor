#pragma once

#include "factory.h"

class Grayscale : public Filter {
public:
    Grayscale() = default;

    static std::unique_ptr<Grayscale> CreateGrayscale();

    void Apply(BmpHolder &image) const override;
};
