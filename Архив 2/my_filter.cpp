#include "my_filter.h"
#include "math.h"

MyFilter::MyFilter(const MyFilterParams &params) : params_(params) {
}

std::unique_ptr<MyFilter> MyFilter::CreateMyFilter(const MyFilterParams &params) {
    return std::make_unique<MyFilter>(params);
}

void MyFilter::Apply(BmpHolder &image) const {
    std::vector<std::vector<Pixel>> new_color_table = image.color_table;
    double swirl_center_y = image.dibHeader.ImageWidth / 2.;                                       // NOLINT
    double swirl_center_x = image.dibHeader.ImageHeight / 2.;                                      // NOLINT
    double swirl_radius = std::min(image.dibHeader.ImageWidth, image.dibHeader.ImageHeight) / 2.;  // NOLINT
    // double swirlTwists = 5;
    for (size_t i = 0; i < image.dibHeader.ImageHeight; i++) {
        for (size_t j = 0; j < image.dibHeader.ImageWidth; j++) {
            double pixel_x = static_cast<double>(i) - swirl_center_x;
            double pixel_y = static_cast<double>(j) - swirl_center_y;
            double pixel_distance = pow(pow(pixel_x, 2) + pow(pixel_y, 2), 0.5);  // NOLINT
            double pixel_angle = atan2(pixel_x, pixel_y);
            double swirl_amount = 1.0 - (pixel_distance / swirl_radius);
            if (swirl_amount > 0.0) {
                double twist_angle = params_.swirlTwists * swirl_amount * M_PI * 2.0;  // NOLINT
                pixel_angle += twist_angle;
                pixel_x = cos(pixel_angle) * pixel_distance;
                pixel_y = sin(pixel_angle) * pixel_distance;
            }
            new_color_table[static_cast<size_t>(swirl_center_x + pixel_x)]
                           [static_cast<size_t>(swirl_center_y + pixel_y)] = image.color_table[i][j];
        }
    }
    image.color_table = new_color_table;
}
