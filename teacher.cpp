#include <vector>
#include <string>
#include <iostream>

#include "opencv2/opencv.hpp"
#include "colors.h"
#include "algorithms.h"
#include "teacher.h"

using namespace cv;
using namespace std;


Mat takeImage(VideoCapture cap) {
    Mat frame;

    cout << endl;
    cout << "Press space to capture an image." << endl;
    cout << endl;

    // loop until image taken
    while (true) {
        cap >> frame;
        // video has been disconnected
        if(frame.empty())
        {
            break;
        }

        // Show the frames
        imshow("Video Capture", frame);
        char key = (char) waitKey(30);
        // exit when q, esc, or space are pressed
        if (key == 'q' || key == 27 || key == 32)
        {
            break;
        }
    }

    return frame;
}


vector<vector<string>> captureCube(VideoCapture cap) {
    int sideCount = 0;
    vector<vector<string>> fullCube;

    // loop until all middle sides have been captured
    while (sideCount < 4) {

        Mat frame = takeImage(cap);
        vector<string> singleSide;

        bool successCheck = thresholdColors(frame, singleSide);

        // if true, one side has been successfully captured
        if (successCheck) {
            // set to capture next side
            sideCount++;
            fullCube.push_back(singleSide);

            if (sideCount != 4){
                cout << "Rotate the cube to the left." << endl;
                cout << endl;
            }
        }

        destroyAllWindows();

    }

    return fullCube;
}


int main(int argc, char** argv)
{
    // open the usb camera, use 0 for default camera;
    VideoCapture cap(2);

    // Check VideoCapture documentation.
    if(!cap.open(2)) {
        cout << "UNABLE TO LOAD CAMERA" << endl;
        return 0;
    }

    // capture vector containing pieces and positions of cube
    vector<vector<string>> fullCube = captureCube(cap);

    string topColor;

    cout << "Enter the color of the center piece on the top of the cube (all lowercase): ";
    cin >> topColor;
    cout << endl;

    // print algorithm needed for OLL
    determineOLL(fullCube, topColor);

    // recapture cube
    fullCube = captureCube(cap);

    // print algorithm needed for PLL
    determinePLL(fullCube);


    return 0;
}
