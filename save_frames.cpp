#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>

#include "opencv2/opencv.hpp"

#include "sm64.h"
#include "util.h"

using namespace cv;
using namespace std;

// This saves a number of frames in a tsv file and also displays
// the frames in a window.
void save_star_frames(cv::VideoCapture& cap, int star_number,
                      int num_frames, const string& directory) {
    namedWindow("video", 1);

    ofstream file;
    file.open(directory + "star_" + to_string(star_number) + ".dat");

    Mat frame;
    int counter = 0;

    while (counter < num_frames) {
        if (waitKey(30) == 27)
		    break;
        cap >> frame;

        Mat cur_num_region = NumberRegion::parse_frame(frame).clone();

        uchar *p1 = cur_num_region.ptr<uchar>(0);
        int num_cols = cur_num_region.cols;
        int num_rows = cur_num_region.rows;
        for (int row = 0; row < num_rows; row++) {
            for (int col = 0; col < num_cols; col++) {
                int base = (row*num_cols + col)*3;
                for (int i = 0; i < 3; i++) {
                    file << counter << "\t" << row << "\t" << col << "\t" <<
                            (base + i) << "\t" <<
                            static_cast<int>(p1[base + i]) << endl;
                }
            }
        }
        
        imshow("video", frame);

        cout << counter << endl;
        counter++;
    }

    file.close();
}

// This makes a histogram of the values of each pixel. Hit ESC for it to
// stop collecting data. Only non-zero values will be written.
void save_pixel_histogram(cv::VideoCapture& cap, int star_number,
                          const string& directory) {
    Rect rect = NumberRegion::rect();

    Mat frame;
    
    int width = NumberRegion::width;
    int height = NumberRegion::height;

    vector<vector<int>*> counts(width*height*3);
    for (int i = 0; i < counts.size(); i++)
         counts[i] = new vector<int>(256, 0);

    while (true) {
        if (waitKey(30) == 27)
		    break;

        cap >> frame;

        imshow("video", frame);

        Mat region = Mat(frame, rect).clone();

        uchar *p1 = region.ptr<uchar>(0);

        for (int i = 0; i < width*height*3; i++)
            (*counts[i])[p1[i]]++;
    }

    ofstream file;
    file.open(directory + "star_histogram_" + to_string(star_number) + ".dat");

    for (int i = 0; i < width*height*3; i++) {
        std::vector<int>* vec = counts[i];
        for (int j = 0; j < 256; j++) {
            if ((*vec)[j] != 0) {
                file << i << "\t" << j << "\t" <<
                       (*vec)[j] << std::endl;
            }
        }
    }

    file.close();
}