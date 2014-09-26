#ifndef SM64_H_
#define SM64_H_

#include <string>

#include "opencv2/opencv.hpp"

struct NumberRegion {
    static cv::Rect rect() {
        return cv::Rect(x, y, width, height);
    }

    static cv::Mat parse_frame(cv::Mat& in) {
        return cv::Mat(in, rect());
    }

    static const int x = 520;
    static const int y = 32;
    static const int width = 80;
    static const int height = 33;
};

cv::VideoCapture init_video_capture();

void save_star_frames(cv::VideoCapture& cap, int star_number,
                      int num_frames, const std::string& directory);

void save_pixel_histogram(cv::VideoCapture& cap, int star_number,
                          const std::string& directory);

#endif  // SM64_H_