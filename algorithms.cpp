#include <vector>
#include <string>
#include <iostream>

#include "algorithms.h"

using namespace std;


bool examineSideOLL(vector<vector<string>>& fullCube, string topColor, int sideNum) {
    vector<string> frontSide = fullCube[sideNum];

    vector<string> rightSide = fullCube[(sideNum+1)%4];
    vector<string> backSide = fullCube[(sideNum+2)%4];
    vector<string> leftSide = fullCube[(sideNum+3)%4];

    string algorithm;

    // two cases where top left and top right of front side are both color of top side of cube
    if ((frontSide[0] == topColor) && (frontSide[2] == topColor)) {

        // symmetry cross
        if ((backSide[0] == topColor) && (backSide[2] == topColor)) {
            algorithm = "F(R U R' U') (R U R' U') (R U R' U') F'";
        }
        // headlights
        else if ((leftSide[0] != topColor) && (rightSide[2] != topColor)) {
            algorithm = "(R2' D) (R' U2) (R D') (R' U2 R')";
        }

    }
    // non symmetry cross
    else if ((frontSide[2] == topColor) && (leftSide[0] == topColor) && (leftSide[2] == topColor) && (backSide[0] == topColor)) {
        algorithm = "(R U2') (R2' U') (R2 U') (R2' U2' R)";
    }
    // sune
    else if ((frontSide[2] == topColor) && (rightSide[2] == topColor) && (backSide[2] == topColor)) {
        algorithm = "R U R' U R U2 R'";
    }
    // anti sune
    else if ((frontSide[0] == topColor) && (rightSide[0] == topColor) && (backSide[0] == topColor)) {
        algorithm = "R' U' R U' R' U2 R";
    }
    // chameleon
    else if ((frontSide[0] == topColor) && (backSide[2] == topColor) && (rightSide[0] != topColor) && (rightSide[2] != topColor)) {
        algorithm = "(r U R' U') (r' F R F')";
    }
    // bow tie
    else if ((frontSide[2] == topColor) && (leftSide[0] == topColor)) {
        algorithm = "F'(r U R' U') (r' F R)";
    }
    // no algorithm found
    else {
        return false;
    }

    cout << "Hold the cube with the " << frontSide[4] << " side facing you";
    cout << " and perform the following operation: " << endl;

    cout << algorithm << endl;

    return true;
}


void determineOLL(vector<vector<string>>& fullCube, string topColor) {

    bool examineResult = false;

    // examine each side to identify algorithm needed
    for (unsigned int i = 0; i < fullCube.size(); i++) {
        examineResult = examineSideOLL(fullCube, topColor, i);

        if (examineResult) {
            return;
        }
    }

    cout << "Unable to determine algorithm" << endl;

}


bool examineSidePLL(vector<vector<string>>& fullCube, int sideNum) {
    vector<string> frontSide = fullCube[sideNum];

    vector<string> rightSide = fullCube[(sideNum+1)%4];
    vector<string> backSide = fullCube[(sideNum+2)%4];
    vector<string> leftSide = fullCube[(sideNum+3)%4];

    string currentSide = frontSide[4];
    string algorithm;

    // shooting edges to adjacent place
    if ((frontSide[1] == rightSide[4]) && (rightSide[1] == frontSide[4]) && (backSide[1] == leftSide[4]) && (leftSide[1] == backSide[4])) {
        algorithm = "M2 U M2 U M' U2 M2 U2 M' U2";
    }
    // shooting edges to its opposite place
    else if ((frontSide[1] == backSide[4]) && (backSide[1] == frontSide[4]) && (rightSide[1] == leftSide[4]) && (leftSide[1] == rightSide[4])) {
        algorithm = "M2 U M2 U2 M2 U M2";
    }
    // cycling 3 edges clockwise
    else if ((frontSide[1] == leftSide[4]) && (leftSide[1] == rightSide[4]) && (rightSide[1] == frontSide[4])) {
        algorithm = "R2 U R U R' U' R' U' R' U R'";
    }
    // cycling 3 edges anti clockwise
    else if ((frontSide[1] == rightSide[4]) && (rightSide[1] == leftSide[4]) && (leftSide[1] == frontSide[4])) {
        algorithm = "R U' R U R U R U' R' U R2";
    }
    // no algorithm found
    else {
        return false;
    }

    cout << "Hold the cube with the " << currentSide << " side facing you";
    cout << " and perform the following operation: " << endl;

    cout << algorithm << endl;
    cout << endl;

    cout << "Congrats the cube is now solved!" << endl;

    return true;
}


void determinePLL(vector<vector<string>>& fullCube) {

    bool examineResult = false;

    // examine each side to identify algorithm needed
    for (unsigned int i = 0; i < fullCube.size(); i++) {
        examineResult = examineSidePLL(fullCube,i);

        if (examineResult) {
            return;
        }
    }

    cout << "Unable to determine algorithm" << endl;
}
