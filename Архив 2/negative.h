#pragma once

#include "factory.h"

class Negative : public Filter {
public:
    Negative() = default;

    static std::unique_ptr<Negative> CreateNegative();

    void Apply(BmpHolder &image) const override;
};
