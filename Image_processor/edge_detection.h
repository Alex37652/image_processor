#pragma once

#include "factory.h"
#include "grayscale.h"
#include "conv_filter.h"

class EdgeDetection : public ConvFilter {
public:
    explicit EdgeDetection(const EdgeDetectionParams &params);

    static std::unique_ptr<EdgeDetection> CreateEdgeDetection(const EdgeDetectionParams &params);

    void Apply(BmpHolder &image) const override;

private:
    Grayscale gs_;
    EdgeDetectionParams params_;
};
