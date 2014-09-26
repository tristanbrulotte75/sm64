#include "opencv2/opencv.hpp"

#include "sm64.h"

int main() {
    cv::VideoCapture cap = init_video_capture();
    save_pixel_histogram(cap, 120, "C:\\Users\\robert\\");
}