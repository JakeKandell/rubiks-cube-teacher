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

    // two cases where top left and top right of front side are both color of top side of cube
    if ((frontSide[0] == topColor) && (frontSide[2] == topColor)) {

        // symmetry cross
        if ((backSide[0] == topColor) && (backSide[2] == topColor)) {
            cout << "Hold the cube with the " << frontSide[4] << " side facing you";
            cout << " and perform the following operation: " << endl;

            cout << "F(R U R' U') (R U R' U') (R U R' U') F'" << endl;
            return true;
        }
        // headlights
        else if ((leftSide[0] != topColor) && (rightSide[2] != topColor)) {
            cout << "Hold the cube with the " << frontSide[4] << " side facing you";
            cout << " and perform the following operation: " << endl;

            cout << "(R2' D) (R' U2) (R D') (R' U2 R')" << endl;
            return true;
        }

    }
    // non symmetry cross
    else if ((frontSide[2] == topColor) && (leftSide[0] == topColor) && (leftSide[2] == topColor) && (backSide[0] == topColor)) {
        cout << "Hold the cube with the " << frontSide[4] << " side facing you";
        cout << " and perform the following operation: " << endl;

        cout << "(R U2') (R2' U') (R2 U') (R2' U2' R)" << endl;
        return true;
    }
    // sune
    else if ((frontSide[2] == topColor) && (rightSide[2] == topColor) && (backSide[2] == topColor)) {
        cout << "Hold the cube with the " << frontSide[4] << " side facing you";
        cout << " and perform the following operation: " << endl;

        cout << "R U R' U R U2 R'" << endl;
        return true;
    }
    // anti sune
    else if ((frontSide[0] == topColor) && (rightSide[0] == topColor) && (backSide[0] == topColor)) {
        cout << "Hold the cube with the " << frontSide[4] << " side facing you";
        cout << " and perform the following operation: " << endl;

        cout << "R' U' R U' R' U2 R" << endl;
        return true;
    }
    // chameleon
    else if ((frontSide[0] == topColor) && (backSide[2] == topColor) && (rightSide[0] != topColor) && (rightSide[2] != topColor)) {
        cout << "Hold the cube with the " << frontSide[4] << " side facing you";
        cout << " and perform the following operation: " << endl;

        cout << "(r U R' U') (r' F R F')" << endl;
        return true;
    }
    // bow tie
    else if ((frontSide[2] == topColor) && (leftSide[0] == topColor)) {
        cout << "Hold the cube with the " << frontSide[4] << " side facing you";
        cout << " and perform the following operation: " << endl;

        cout << "F'(r U R' U') (r' F R)" << endl;

        return true;
    }
    // no algorithm found
    else {
        return false;
    }
}

void determineOLL(vector<vector<string>>& fullCube, string topColor) {

    bool examineResult = false;

    // examine each side to identify algorithm needed
    for (unsigned int i = 0; i < fullCube.size(); i++) {
        examineResult = examineSideOLL(fullCube, topColor, i);

        if (examineResult) {
            break;
        }
    }

}

void determinePLL(vector<vector<string>>& fullCube, string topColor) {

}

void determineAlgorithms(vector<vector<string>>& fullCube, string topColor) {
    determineOLL(fullCube, topColor);
}
