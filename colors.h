#include "opencv2/opencv.hpp"
#include <vector>

void thresholdOneColor(cv::Mat& frameHSV, cv::Mat& frameContours, cv::Scalar lowThresh, cv::Scalar highThresh,  std::vector<std::vector<cv::Point>>& contours, std::vector<cv::Vec4i>& hierarchy);

void thresholdColors(cv::Mat frame);
