#include <vector>
#include <string>
#include "opencv2/opencv.hpp"

cv::Mat takeImage(cv::VideoCapture cap);

std::vector<std::vector<std::string>> captureCube(cv::VideoCapture cap);
