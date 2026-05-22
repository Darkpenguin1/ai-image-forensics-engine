#include "EdgeAnalysis.hpp"
#include <cmath>



/*
Sobel Determines how fast brightness changes around a pixel. If neighboring pixels have similar values 
The area is smooth and if neighboring pixels have different values the area is an edge.

Gx measures left-to-right brightness change.

Gy measures top-to-bottom brightness change.

sumX = horizontal brightness-change score
sumY = vertical brightness-change score
magnitude = total edge strength at this pixel

***Params gray: grayscale image to analyze
***Returns: a new image where each pixel's value is the magnitude of the edge at that pixel in the original image. Higher values indicate stronger edges.

*/
cv::Mat EdgeAnalysis::sobelMagnitude(const cv::Mat& gray){

    int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int sobelY[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
        
    };

    cv::Mat magnitudeImage = cv::Mat::zeros(gray.rows, gray.cols, CV_64F);	

    for (int row = 1; row < gray.rows - 1; row++){
    	for (int col = 1; col < gray.cols - 1; col++){
	    
	        int sumX = 0, sumY = 0;
            
            for (int i = -1; i <= 1; i++){
                for (int j = -1; j <= 1; j++){
                    int pixel = gray.at<uchar>(row + i, col + j);

                    sumX += pixel * sobelX[i + 1][j + 1];
                    sumY += pixel * sobelY[i + 1][j + 1];
                }
	    }
 	    double magnitude = std::sqrt(sumX * sumX + sumY * sumY);	    
        magnitudeImage.at<double>(row, col) = magnitude;
	}
    
    
    }
    return magnitudeImage;  
}


EdgeStats EdgeAnalysis::computeEdgeStats(const cv::Mat& gray) {
    cv::Mat magnitudeImage = sobelMagnitude(gray);

    double threshold = 50.0;

    int edgePixels = 0;
    int totalPixels = 0;
    double gradientSum = 0.0;

    for (int row = 1; row < magnitudeImage.rows - 1; row++) {
        for (int col = 1; col < magnitudeImage.cols - 1; col++) {
            double magnitude = magnitudeImage.at<double>(row, col);

            if (magnitude > threshold) {
                edgePixels++;
            }

            gradientSum += magnitude;
            totalPixels++;
        }
    }

    EdgeStats stats{};

    if (totalPixels == 0) {
        stats.edgeDensity = 0.0;
        stats.averageGradient = 0.0;
        stats.sharpness = 0.0;
        return stats;
    }

    stats.edgeDensity = static_cast<double>(edgePixels) / totalPixels;
    stats.averageGradient = gradientSum / totalPixels;

    // For now, sharpness can be average gradient.
    // Later, replace this with Laplacian variance.
    stats.sharpness = stats.averageGradient;

    return stats;
}