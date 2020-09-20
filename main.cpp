#include "opencv2/opencv.hpp"
#include "iostream"

using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap(3);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(3))
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

    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);

    while (1) {
        imshow("Color Shifted", hsv);
        if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC
    }

    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}
