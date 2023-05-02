#include "edge_detection.h"
#include <algorithm>

EdgeDetection::EdgeDetection(const EdgeDetectionParams &params) : gs_(), params_(params) {
}

std::unique_ptr<EdgeDetection> EdgeDetection::CreateEdgeDetection(const EdgeDetectionParams &params) {
    return std::make_unique<EdgeDetection>(params);
}

void EdgeDetection::Apply(BmpHolder &image) const {
    gs_.Apply(image);
    std::vector<std::vector<Pixel>> new_color_table = Convolution(image, 4);

    for (size_t i = 0; i < image.color_table.size(); ++i) {
        for (size_t j = 0; j < image.color_table[0].size(); ++j) {
            image.color_table[i][j].b = std::clamp(new_color_table[i][j].b, 0., 1.);
            image.color_table[i][j].g = std::clamp(new_color_table[i][j].g, 0., 1.);
            image.color_table[i][j].r = std::clamp(new_color_table[i][j].r, 0., 1.);
            if (image.color_table[i][j].b > params_.threshold || image.color_table[i][j].g > params_.threshold ||
                image.color_table[i][j].r > params_.threshold) {
                image.color_table[i][j] = {1, 1, 1};
            } else {
                image.color_table[i][j] = {0, 0, 0};
            }
        }
    }
}
