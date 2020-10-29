#include "colors.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace cv;
using namespace std;

// compare function used to sort by x coordinate
bool xCmp(Point a, Point b) {
    return a.x < b.x;
}


// compare function used to sort by y coordinate
bool yCmp(Point a, Point b) {
    return a.y < b.y;
}


void sortPieces(vector<Point>& pieceLocations) {
    // sorts pieces by y coordinate
    sort(pieceLocations.begin(), pieceLocations.end(), yCmp);

    // sorts pieces in first row by x coordinates
    sort(pieceLocations.begin(), pieceLocations.begin()+3, xCmp);

    // sorts pieces in second row by x coordinates
    sort(pieceLocations.begin()+3, pieceLocations.begin()+6, xCmp);

    // sorts pieces in third row by x coordinates
    sort(pieceLocations.begin()+6, pieceLocations.end(), xCmp);

}

void thresholdOneColor(Mat& frameHSV, Mat& frameContours, Scalar lowThresh, Scalar highThresh, vector<vector<Point>>& allContours, vector<Point>& piecesOnly, vector<string>& colorsOnly, string color) {

    Mat frameThreshold;

    // theshold image for specific color
    inRange(frameHSV, lowThresh, highThresh, frameThreshold);

    // debug code used to show orig image with threshold view
    // while (true) {
    //     imshow("Saved Image", frameContours);
    //     imshow("Saved Threshold", frameThreshold);
    //
    //     char key = (char) waitKey(30);
    //     if (key == 'q' || key == 27)
    //     {
    //         break;
    //     }
    // }

    // kernels used for morphology operations
    Mat kernelOpen = getStructuringElement(0, Size(5, 5), Point(-1, -1));
    Mat kernelClose = getStructuringElement(0, Size(5, 5), Point(-1, -1));

    // opening operation to remove small noise
    morphologyEx(frameThreshold, frameThreshold, 2, kernelOpen);
    // closing operation to fill in holes
    morphologyEx(frameThreshold, frameThreshold, 3, kernelClose);

    // debug code to show before and after morphological operations
    // while (true) {
    //     imshow("Updated Threshold", frameThreshold);
    //
    //     char key = (char) waitKey(30);
    //     if (key == 'q' || key == 27)
    //     {
    //         break;
    //     }
    // }

    // use canny edge detection
    Mat cannyOutput;
    Canny(frameThreshold, cannyOutput, 100, 200);

    vector<vector<Point>> tempContours;
    vector<Vec4i> tempHierarchy;
    // find countours of threshold
    findContours(cannyOutput, tempContours, tempHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // picks a random color to draw countours
    Scalar randColor = Scalar(rand()&255, rand()&255, rand()&255);
    // draws countours onto image
    for(size_t i = 0; i< tempContours.size(); i++) {
        drawContours(frameContours, tempContours, (int)i, randColor, 2, LINE_8, tempHierarchy, 0);
    }

    destroyAllWindows();

    vector<vector<Point>> noDupes;

    for (unsigned int i=0; i < tempContours.size(); i += 2) {
        // removes duplicates that are next to each other
        noDupes.push_back(tempContours[i]);

        Rect boundingRectangle = boundingRect(tempContours[i]);
        Point topLeft = boundingRectangle.tl();

        // pushes back point and color into two vectors
        piecesOnly.push_back(topLeft);
        colorsOnly.push_back(color);
    }

    allContours.insert(allContours.end(), noDupes.begin(), noDupes.end());

}


bool thresholdColors(Mat frame, vector<string>& fullSide) {

    // seed for random colors for contours
    srand(time(NULL));

    Mat frameContours = frame;
    Mat frameHSV;

    // Convert from BGR to HSV colorspace
    cvtColor(frame, frameHSV, COLOR_BGR2HSV);

    // initalizing contour vector
    vector<vector<Point>> allContours;

    // indexes correlate with each other
    vector<Point> piecesOnly;
    vector<string> colorsOnly;

    // thresholds red
    thresholdOneColor(frameHSV, frameContours, Scalar(0, 223, 162), Scalar(180, 255, 200), allContours, piecesOnly, colorsOnly, "red");
    // thresholds orange
    thresholdOneColor(frameHSV, frameContours, Scalar(0, 183, 220), Scalar(23, 255, 255), allContours, piecesOnly, colorsOnly, "orange");
    // thresholds yellow
    thresholdOneColor(frameHSV, frameContours, Scalar(21, 90, 212), Scalar(40, 206, 255), allContours, piecesOnly, colorsOnly, "yellow");
    // thresholds green
    thresholdOneColor(frameHSV, frameContours, Scalar(43, 61, 156), Scalar(68, 125, 238), allContours, piecesOnly, colorsOnly, "green");
    // thresholds blue
    thresholdOneColor(frameHSV, frameContours, Scalar(89, 105, 103), Scalar(129, 235, 191), allContours, piecesOnly, colorsOnly, "blue");
    // thresholds white
    thresholdOneColor(frameHSV, frameContours, Scalar(0, 0, 236), Scalar(36, 40, 255), allContours, piecesOnly, colorsOnly, "white");

    cout << "Have all pieces been correctly identified on this side?" << endl;
    cout << "Press 'y' for yes and 'n' for no." << endl;
    cout << endl;

    // shows image of cube with contours drawn around identified pieces
    while (true) {
        imshow("Identified Pieces", frameContours);

        char key = (char) waitKey(30);
        // case if image looks fine
        if (key == 'y')
        {
            break;
        }
        // case if user recognizes an error in the processing
        else if (key == 'n') {
            cout << "Failed to properly identify pieces. Try taking another picture." << endl;
            return false;
        }
    }

    // failed to find proper number of squares
    if (allContours.size() != 9) {
        cout << "Incorrect number of squares identified. Try taking another picture." << endl;
        return false;
    }

    vector<Point> pieceLocations;

    // loops through each countour and pushes back top left point into new vector
    for (unsigned int i=0; i < allContours.size(); i++) {
        Rect boundingRectangle = boundingRect(allContours[i]);

        Point topLeft = boundingRectangle.tl();
        pieceLocations.push_back(topLeft);
    }

    // sorts pieces into 1-9 order
    sortPieces(pieceLocations);

    cout << endl;

    // loops through sorted pieces in order from top left to bottom right
    for (unsigned int i = 0; i < pieceLocations.size(); i++) {

        Point currentPoint = pieceLocations[i];

        // looks for point in vector of only pieces
        vector<Point>::iterator it = find(piecesOnly.begin(), piecesOnly.end(), currentPoint);

        int index = -1;

        // if point is found gets index of point
        if (it != piecesOnly.end()){
            index = distance(piecesOnly.begin(), it);
        }

        // uses index to get corresponding color of piece at that point
        fullSide.push_back(colorsOnly[index]);

    }

    // side identification has succeeded if we have reached here
    return true;
}
