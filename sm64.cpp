#include "sm64.h"
#include "opencv2/opencv.hpp"

cv::VideoCapture init_video_capture() {
    cv::VideoCapture cap;
    cap.open(1);

    if (!cap.isOpened()) {
        printf("Error: could not load a camera or video.\n");
    }

    cv::Mat frame;

    cap >> frame;
    if (!frame.data) {
        printf("Error: no frame data.\n");
        exit(1);
    }

    return cap;
}