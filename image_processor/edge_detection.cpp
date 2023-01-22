#include "edge_detection.h"

EdgeDetection::EdgeDetection(const EdgeDetectionParams &params) : gs_(), params_(params) {
}

std::unique_ptr<EdgeDetection> EdgeDetection::CreateEdgeDetection(const EdgeDetectionParams &params) {
    return std::make_unique<EdgeDetection>(params);
}

void EdgeDetection::Apply(BmpHolder &image) const {
    gs_.Apply(image);
    Pixel new_pixel;
    std::vector<std::vector<Pixel>> new_color_table(image.color_table.size(),
                                                    std::vector<Pixel>(image.color_table[0].size()));
    for (size_t i = 0; i < image.color_table.size(); ++i) {
        for (size_t j = 0; j < image.color_table[0].size(); ++j) {
            new_pixel = image.color_table[i][j] * 4.;
            if (i > 0) {
                new_pixel -= image.color_table[i - 1][j];
            } else {
                new_pixel -= image.color_table[i][j];
            }
            if (j > 0) {
                new_pixel -= image.color_table[i][j - 1];
            } else {
                new_pixel -= image.color_table[i][j];
            }
            if (i < image.color_table.size() - 1) {
                new_pixel -= image.color_table[i + 1][j];
            } else {
                new_pixel -= image.color_table[i][j];
            }
            if (j < image.color_table[0].size() - 1) {
                new_pixel -= image.color_table[i][j + 1];
            } else {
                new_pixel -= image.color_table[i][j];
            }
            new_color_table[i][j].b = std::min(1., std::max(0., new_pixel.b));
            new_color_table[i][j].g = std::min(1., std::max(0., new_pixel.g));
            new_color_table[i][j].r = std::min(1., std::max(0., new_pixel.r));
            if (new_color_table[i][j].b > params_.threshold || new_color_table[i][j].g > params_.threshold ||
                new_color_table[i][j].r > params_.threshold) {
                new_color_table[i][j] = {1, 1, 1};
            } else {
                new_color_table[i][j] = {0, 0, 0};
            }
        }
    }
    image.color_table = new_color_table;
}
