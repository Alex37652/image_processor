#pragma once

#include "factory.h"
#include "grayscale.h"

class EdgeDetection : public Filter {
public:
    EdgeDetection(const EdgeDetectionParams &params);

    static std::unique_ptr<EdgeDetection> CreateEdgeDetection(const EdgeDetectionParams &params);

    void Apply(BmpHolder &image) const override;

private:
    Grayscale gs_;
    EdgeDetectionParams params_;
};
