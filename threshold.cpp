#include <vector>
#include <string>
#include <iostream>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


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


int main(int argc, char** argv) {

    // create named windows
    namedWindow(window_detection_name);
    namedWindow(window_capture_name);

    // Trackbars to set thresholds for HSV values
    createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
    createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
    createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
    createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
    createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
    createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);

    // create frame variables
    Mat frame;
    Mat frame_hsv;
    Mat frame_threshold;

    // open the usb camera, use 0 for default camera;
    VideoCapture cap(2);

    // Check VideoCapture documentation.
    if(!cap.open(2))
        return 0;

    cout << "Move sliders to adjust thresholds. Press 'q' or 'esc' to exit program." << endl;

    // loop until user exits
    while (true) {
        cap >> frame;
        if(frame.empty())
        {
            break;
        }
        // Convert from BGR to HSV colorspace
        cvtColor(frame, frame_hsv, COLOR_BGR2HSV);

        // Detect the object based on HSV Range Values
        inRange(frame_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);

        // Show the frames
        imshow(window_detection_name, frame_threshold);
        imshow(window_capture_name, frame);

        // exit if user presses q or esc
        char key = (char) waitKey(30);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }

    destroyAllWindows();

    return 0;
}
