#include "parser.h"
#include "filter_structure.h"
#include "bmp_reader_writer.h"
#include "factory.h"
#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "gaussian_blur.h"
#include "my_filter.h"

#include <stdexcept>
#include <iostream>

int main(int argc, char **argv) {
    Parser parser;

    std::string input_file;
    std::string output_file;

    CropParams crop_params;
    BlurParams blur_params;
    EdgeDetectionParams edge;
    MyFilterParams my_params;

    Factory factory;

    parser.AddPositionalArg("input_file", &input_file);
    parser.AddPositionalArg("output_file", &output_file);
    parser.AddKeywordArg("-crop", {
                                      {"width", &crop_params.width},
                                      {"height", &crop_params.height},
                                  });
    parser.AddKeywordArg("-blur", {{"sigma", &blur_params.sigma}});
    parser.AddKeywordArg("-gs", {});
    parser.AddKeywordArg("-neg", {});
    parser.AddKeywordArg("-sharp", {});
    parser.AddKeywordArg("-edge", {{"threshold", &edge.threshold}});
    parser.AddKeywordArg("-my", {{"degree", &my_params.swirlTwists}});

    try {
        parser.Parse(argc, argv);
    } catch (std::invalid_argument const &) {
        std::cout << "Incorrect amount of arguments";
    } catch (const char *error) {
        std::cout << error;
    }

    factory.Register("-crop", std::bind(Crop::CreateCrop, crop_params));
    factory.Register("-gs", Grayscale::CreateGrayscale);
    factory.Register("-neg", Negative::CreateNegative);
    factory.Register("-sharp", Sharpening::CreateSharpening);
    factory.Register("-edge", std::bind(EdgeDetection::CreateEdgeDetection, edge));
    factory.Register("-blur", std::bind(GaussianBlur::CreateGaussianBlur, blur_params));
    factory.Register("-my", std::bind(MyFilter::CreateMyFilter, my_params));

    BmpHolder image;
    Read(input_file, image);

    for (auto &filter : parser.GetFilters()) {
        factory.Create(filter)->Apply(image);
    }

    Write(output_file, image);
    return 0;
}
