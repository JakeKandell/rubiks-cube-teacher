#include "colors.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

void thresholdOneColor(Mat& frameHSV, Mat& frameContours, Scalar lowThresh, Scalar highThresh, vector<vector<Point>>& allContours, vector<Vec4i>& hierarchy) {

    Mat frameThreshold;

    // theshold image for specific color
    inRange(frameHSV, lowThresh, highThresh, frameThreshold);

    // shows orig image with threshold
    while (true) {
        imshow("Saved Image", frameContours);
        imshow("Saved Threshold", frameThreshold);

        char key = (char) waitKey(30);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }

    // kernels used for morphology operations
    Mat kernelOpen = getStructuringElement(0, Size(5, 5), Point(-1, -1));
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

    vector<vector<Point>> tempContours;
    vector<Vec4i> tempHierarchy;
    // find countours of threshold
    findContours(cannyOutput, tempContours, tempHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // picks a random color to draw countours
    Scalar color = Scalar(rand()&255, rand()&255, rand()&255);
    // draws countours onto image
    for(size_t i = 0; i< tempContours.size(); i++) {
        drawContours(frameContours, tempContours, (int)i, color, 2, LINE_8, tempHierarchy, 0);
    }

    while (true) {
        imshow("With Countours", frameContours);

        char key = (char) waitKey(30);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }

    destroyAllWindows();

    allContours.insert(allContours.end(), tempContours.begin(), tempContours.end());

}


void thresholdColors(Mat frame) {

    srand(time(NULL));

    Mat frameContours = frame;
    Mat frameHSV;

    vector<vector<Point>> allContours;
    vector<Vec4i> hierarchy;

    // Convert from BGR to HSV colorspace
    cvtColor(frame, frameHSV, COLOR_BGR2HSV);

    // thresholds red
    thresholdOneColor(frameHSV, frameContours, Scalar(0, 238, 163), Scalar(4, 255, 204), allContours, hierarchy);
    // thresholds orange
    thresholdOneColor(frameHSV, frameContours, Scalar(4, 183, 220), Scalar(23, 255, 255), allContours, hierarchy);
    // thresholds yellow
    thresholdOneColor(frameHSV, frameContours, Scalar(21, 90, 212), Scalar(40, 206, 255), allContours, hierarchy);
    // thresholds green
    thresholdOneColor(frameHSV, frameContours, Scalar(43, 61, 156), Scalar(68, 125, 238), allContours, hierarchy);
    // thresholds blue
    thresholdOneColor(frameHSV, frameContours, Scalar(89, 105, 103), Scalar(129, 235, 191), allContours, hierarchy);
    // thresholds white
    thresholdOneColor(frameHSV, frameContours, Scalar(0, 0, 237), Scalar(40, 56, 255), allContours, hierarchy);

    cout << "Contours Size: " << allContours.size()/2 << endl;

    for (unsigned int i=0; i < allContours.size(); i += 2) {
        Rect boundingRectangle = boundingRect(allContours[i]);

        cout << boundingRectangle << endl;

        Point topLeft = boundingRectangle.tl();
        cout << topLeft << endl;

        Size rectSize = boundingRectangle.size();
        cout << rectSize << endl;
    }




    return;
}
