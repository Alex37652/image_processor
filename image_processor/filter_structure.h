#pragma once

#include <cstdlib>

struct CropParams {
    size_t width;
    size_t height;
};

struct BlurParams {
    double sigma;
};

struct EdgeDetectionParams {
    double threshold;
};

struct MyFilterParams {
    double swirlTwists;
};
