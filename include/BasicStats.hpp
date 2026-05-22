#pragma once
#include <opencv2/opencv.hpp>

struct BrightnessStats {
    double average;
    int min;
    int max;
};

class BasicStats {
public:
    static cv::Mat toGrayscale(const cv::Mat& image);
    static BrightnessStats computeBrightnessStats(const cv::Mat& gray);
    static std::vector<int> computeHistogram(const cv::Mat& gray);
    static double computeEntropy(const std::vector<int>& histogram, int totalPixels);
};