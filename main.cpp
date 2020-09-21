#include "opencv2/opencv.hpp"
#include "iostream"

using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap(2);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(2))
        return 0;



    Mat frame;
    while (1)
    {
          cap >> frame;
          if( frame.empty() ) break; // end of video stream
          imshow("this is you, smile! :)", frame);
          if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC
    }




    destroyAllWindows();

    while (1) {
        imshow("Captured Image", frame);
        if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC
    }

    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 0;
    int iHighV = 255;

    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);

    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);

    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);

    while (1) {
        imshow("Control", hsv);
        imshow("Color Shifted", hsv);
        if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC
    }

    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}


/*
Thresholds:

COUCH:

Red:
121, 1, 0
0.5, 100, 47

Orange:
196, 4, 0
1.2, 100, 77

Green:
72, 132, 62
111, 53, 52

Blue:
16, 19, 64
236, 75, 25

White:
188, 171, 143
37, 24, 74

Yellow:
205, 189, 18

BLANK WALL:

Red:
190, 0, 0
0, 100, 75

Orange:
255, 90, 1
21, 100, 100

Green:
139, 209, 120
107, 43, 82

Blue:
21, 48, 139
226, 85, 55

White:
255, 255, 235
60, 9, 100

Yellow
254, 255, 115
60, 55, 100

COMPUTER:

Red:
174, 0, 0
0, 100, 68

Orange:
255, 19, 0
5, 100, 100

Green:
130, 191, 88
96, 54, 75

Blue:
28, 36, 101
233, 72, 40

White:
254, 241, 199
35, 22, 100

Yellow:
254, 250, 18
59, 93, 100

*/
