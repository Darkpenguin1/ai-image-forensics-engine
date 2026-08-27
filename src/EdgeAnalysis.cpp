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

cv::Mat EdgeAnalysis::laplacianFilter(const cv::Mat& gray) {
    int laplacianKernel[3][3] = {
        {0,  1, 0},
        {1, -4, 1},
        {0,  1, 0}
    };

    cv::Mat laplacianImage = cv::Mat::zeros(gray.rows, gray.cols, CV_64F);

    for (int row = 1; row < gray.rows - 1; row++) {
        for (int col = 1; col < gray.cols - 1; col++) {
            double sum = 0.0;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int pixel = gray.at<uchar>(row + i, col + j);
                    sum += pixel * laplacianKernel[i + 1][j + 1];
                }
            }

            laplacianImage.at<double>(row, col) = sum;
        }
    }

    return laplacianImage;
}


cv::Mat EdgeAnalysis::cannyEdge(const cv::Mat& gray, double lowThreshold, double highThreshold) {
    cv::Mat gray8;
    if (gray.type() != CV_8U) {
        gray.convertTo(gray8, CV_8U);
    } else {
        gray8 = gray;
    }

    cv::Mat edges;
    cv::Canny(gray8, edges, lowThreshold, highThreshold);
    return edges;
}


EdgeStats EdgeAnalysis::computeEdgeStats(const cv::Mat& gray) {
    cv::Mat magnitudeImage = sobelMagnitude(gray);
    cv::Mat laplacianImage = laplacianFilter(gray);

    double laplacianSum = 0.0;
    double laplacianSquaredSum = 0.0;
    int laplacianPixels = 0;
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

    // Sharpness is measured using variance of the Laplacian.
    // Higher variance usually means sharper image detail.
    for (int row = 1; row < laplacianImage.rows - 1; row++) {
        for (int col = 1; col < laplacianImage.cols - 1; col++) {
            double value = laplacianImage.at<double>(row, col);

            laplacianSum += value;
            laplacianSquaredSum += value * value;
            laplacianPixels++;
        }
    }

    if (laplacianPixels == 0) {
        stats.sharpness = 0.0;
    } else {
        double mean = laplacianSum / laplacianPixels;
        double variance = (laplacianSquaredSum / laplacianPixels) - (mean * mean);

        stats.sharpness = variance;
    }

    return stats;
}