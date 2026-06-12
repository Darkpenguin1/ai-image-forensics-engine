#pragma once
#include<opencv2/opencv.hpp>

struct EdgeStats{
  double edgeDensity;
  double averageGradient;
  double sharpness;


};

class EdgeAnalysis {
	public:
		static cv::Mat sobelMagnitude(const cv::Mat& gray);
		static cv::Mat laplacianFilter(const cv::Mat& gray);
    static EdgeStats computeEdgeStats(const cv::Mat& gray);
};
