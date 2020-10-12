#include <vector>
#include "opencv2/opencv.hpp"
#include "iostream"
#include "colors.h"

using namespace cv;
using namespace std;

const int max_value_H = 360/2;
const int max_value = 255;
const String window_capture_name = "Video Capture";
const String window_detection_name = "Object Detection";
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;
static void on_low_H_thresh_trackbar(int, void *)
{
    low_H = min(high_H-1, low_H);
    setTrackbarPos("Low H", window_detection_name, low_H);
}
static void on_high_H_thresh_trackbar(int, void *)
{
    high_H = max(high_H, low_H+1);
    setTrackbarPos("High H", window_detection_name, high_H);
}
static void on_low_S_thresh_trackbar(int, void *)
{
    low_S = min(high_S-1, low_S);
    setTrackbarPos("Low S", window_detection_name, low_S);
}
static void on_high_S_thresh_trackbar(int, void *)
{
    high_S = max(high_S, low_S+1);
    setTrackbarPos("High S", window_detection_name, high_S);
}
static void on_low_V_thresh_trackbar(int, void *)
{
    low_V = min(high_V-1, low_V);
    setTrackbarPos("Low V", window_detection_name, low_V);
}
static void on_high_V_thresh_trackbar(int, void *)
{
    high_V = max(high_V, low_V+1);
    setTrackbarPos("High V", window_detection_name, high_V);
}

int main(int argc, char** argv)
{
    VideoCapture cap(2);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(2))
        return 0;

    namedWindow(window_detection_name);
    namedWindow("Video Capture");
    // Trackbars to set thresholds for HSV values
    createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
    createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
    createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
    createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
    createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
    createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);

    Mat frame;
    Mat frame_hsv;
    Mat frame_threshold;

    while (true) {
        cap >> frame;
        if(frame.empty())
        {
            break;
        }
        // // Convert from BGR to HSV colorspace
        cvtColor(frame, frame_hsv, COLOR_BGR2HSV);
        // // Detect the object based on HSV Range Values
        inRange(frame_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
        //inRange(frame_hsv, Scalar(0, 220, 160), Scalar(6, 255, 215), frame_threshold);
        // // Show the frames
        imshow(window_detection_name, frame_threshold);
        imshow("Video Capture", frame);
        char key = (char) waitKey(30);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    thresholdColors(frame);

    // destroyAllWindows();
    //
    // while (true) {
    //     imshow("Saved Image", frame);
    //     imshow("Saved Threshold", frame_threshold);
    //
    //     char key = (char) waitKey(30);
    //     if (key == 'q' || key == 27)
    //     {
    //         break;
    //     }
    // }

    // Mat new_threshold;
    // Mat kernel = getStructuringElement(0, Size(3, 3), Point(-1, -1));
    // Mat kernel2 = getStructuringElement(0, Size(5, 5), Point(-1, -1));
    //
    // morphologyEx(frame_threshold, new_threshold, 2, kernel);
    // morphologyEx(new_threshold, new_threshold, 3, kernel2);
    //
    // while (true) {
    //     imshow("Updated Threshold", new_threshold);
    //
    //     char key = (char) waitKey(30);
    //     if (key == 'q' || key == 27)
    //     {
    //         break;
    //     }
    // }
    //
    // Mat canny_output;
    // Canny(new_threshold, canny_output, 100, 200);
    //
    // vector<vector<Point>> contours;
    // vector<Vec4i> hierarchy;
    // findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    //
    // Mat frame_countours = frame;
    //
    // Scalar color = Scalar(rand()&255, rand()&255, rand()&255);
    // for( size_t i = 0; i< contours.size(); i++ ) {
    //     drawContours(frame_countours, contours, (int)i, color, 1, LINE_8, hierarchy, 0);
    // }
    //
    // while (true) {
    //     imshow("With Countours", frame_countours);
    //
    //     char key = (char) waitKey(30);
    //     if (key == 'q' || key == 27)
    //     {
    //         break;
    //     }
    // }
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}
