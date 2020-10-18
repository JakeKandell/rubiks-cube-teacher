#include "opencv2/opencv.hpp"
#include <vector>
#include <map>
#include <string>

bool yCmp(cv::Point a, cv::Point b);

bool yCmp(cv::Point a, cv::Point b);

void sortPieces(std::vector<cv::Point>& pieceLocations);

void thresholdOneColor(cv::Mat& frameHSV, cv::Mat& frameContours, cv::Scalar lowThresh, cv::Scalar highThresh,  std::vector<std::vector<cv::Point>>& contours, std::vector<cv::Point>& piecesOnly, std::vector<std::string>& colorsOnly, std::string color);

void thresholdColors(cv::Mat frame);
