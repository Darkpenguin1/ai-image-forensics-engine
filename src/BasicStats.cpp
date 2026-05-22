#include "BasicStats.hpp"
#include "cmath"

cv::Mat BasicStats::toGrayscale(const cv::Mat& image) {
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

BrightnessStats BasicStats::computeBrightnessStats(const cv::Mat& gray) {
    double total = 0.0;
    int minVal = 255;
    int maxVal = 0;

    for (int y = 0; y < gray.rows; y++) {
        for (int x = 0; x < gray.cols; x++) {
            int value = gray.at<uchar>(y, x);

            total += value;

            if (value < minVal) minVal = value;
            if (value > maxVal) maxVal = value;
        }
    }

    BrightnessStats stats;
    stats.average = total / (gray.rows * gray.cols);
    stats.min = minVal;
    stats.max = maxVal;
    
    return stats;
}

// Returns vector serving as histogram 
// X axis serves as the brightness value the idx of the vector 
// Y axis is the number of pixels at that brightness value 
std::vector<int> BasicStats::computeHistogram(const cv::Mat& gray){
    std::vector<int> histogram(256,0);

    for (int y = 0; y < gray.rows; y++) {
        for (int x = 0; x < gray.cols; x++) {
            int value = gray.at<uchar>(y, x);
            histogram[value]++; 
        }
    }
    return histogram;
}

// Entropy is how spread out values of brightness are within an img, for ex some imgs are uniform in brightness throughout thus low entropy 
// Formal def: how unpredictable/spread the brightness distribution is
// Formula H = −∑ p(x) * log2​p(x)
// The formula is taking the log of each outcomes probability and adding up all its negative sums
double BasicStats::computeEntropy(const std::vector<int>& histogram, int totalPixels){
    double entropy = 0.0;

    for (int i = 0; i < histogram.size(); i++){

        if (histogram[i] == 0){
            continue;
        }

        double probability = static_cast<double>(histogram[i]) / totalPixels; // probability of a pixel with that brightness occurring
        entropy += probability * std::log2(probability);
    }

    return -entropy;

}