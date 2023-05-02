cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Werror -Wall -Wextra -Wpedantic -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++")

set(SOURCE_FILES)
add_executable(image_processor ${SOURCE_FILES} image_processor.cpp parser.cpp parser.h filter_structure.h bmp_reader_writer.cpp bmp_reader_writer.h factory.cpp factory.h crop.cpp crop.h grayscale.cpp grayscale.h negative.cpp negative.h sharpening.cpp sharpening.h edge_detection.cpp edge_detection.h gaussian_blur.cpp gaussian_blur.h my_filter.cpp my_filter.h filter.h conv_filter.cpp conv_filter.h)

target_include_directories(image_processor PRIVATE sources)

set(CMAKE_PROJECT_ROOT "${CMAKE_SOURCE_DIR}/../../")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_PROJECT_ROOT}/cmake")
#set(TEST_FILES
#        tests/test_for_wo_main1.cpp
#       tests/test_for_wo_main2.cpp
#        )

#add_catch(test_image_processor ${SOURCE_FILES} ${TEST_FILES})
#target_include_directories(test_image_processor PRIVATE sources)
