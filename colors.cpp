#include "colors.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace cv;
using namespace std;

void thresholdOneColor(Mat& frameHSV, Mat& frameCountours, Scalar lowThresh, Scalar highThresh) {

    Mat frameThreshold;

    // theshold image for specific color
    inRange(frameHSV, lowThresh, highThresh, frameThreshold);

    // shows orig image with threshold
    while (true) {
        imshow("Saved Image", frameCountours);
        imshow("Saved Threshold", frameThreshold);

        char key = (char) waitKey(30);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }

    // kernels used for morphology operations
    Mat kernelOpen = getStructuringElement(0, Size(3, 3), Point(-1, -1));
    Mat kernelClose = getStructuringElement(0, Size(5, 5), Point(-1, -1));

    // opening operation to remove small noise
    morphologyEx(frameThreshold, frameThreshold, 2, kernelOpen);
    // closing operation to fill in holes
    morphologyEx(frameThreshold, frameThreshold, 3, kernelClose);

    while (true) {
        imshow("Updated Threshold", frameThreshold);

        char key = (char) waitKey(30);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }

    // use canny edge detection
    Mat cannyOutput;
    Canny(frameThreshold, cannyOutput, 100, 200);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    // find countours of threshold
    findContours(cannyOutput, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // picks a random color to draw countours
    Scalar color = Scalar(rand()&255, rand()&255, rand()&255);
    // draws countours onto image
    for(size_t i = 0; i< contours.size(); i++) {
        drawContours(frameCountours, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    }

    while (true) {
        imshow("With Countours", frameCountours);

        char key = (char) waitKey(30);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }

    destroyAllWindows();

}


void thresholdColors(Mat frame) {

    srand(time(NULL));

    Mat frameCountours = frame;
    Mat frameHSV;

    // Convert from BGR to HSV colorspace
    cvtColor(frame, frameHSV, COLOR_BGR2HSV);

    // thresholds red
    thresholdOneColor(frameHSV, frameCountours, Scalar(0, 238, 163), Scalar(4, 255, 204));
    // thresholds orange
    thresholdOneColor(frameHSV, frameCountours, Scalar(4, 183, 220), Scalar(23, 255, 255));
    // thresholds yellow
    thresholdOneColor(frameHSV, frameCountours, Scalar(21, 90, 212), Scalar(40, 206, 255));
    // thresholds green
    thresholdOneColor(frameHSV, frameCountours, Scalar(43, 61, 156), Scalar(68, 125, 238));
    // thresholds blue
    thresholdOneColor(frameHSV, frameCountours, Scalar(89, 105, 103), Scalar(129, 235, 191));
    // thresholds white
    thresholdOneColor(frameHSV, frameCountours, Scalar(0, 0, 237), Scalar(40, 56, 255));




    return;
}
