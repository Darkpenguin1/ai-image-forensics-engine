#include <iostream>
#include <opencv2/opencv.hpp>
#include "BasicStats.hpp"
#include "EdgeAnalysis.hpp"

int main(int argc, char** argv){

    std::string imageName("../data/grey-rose.jpg");

    if (argc > 1)
    {
        imageName = argv[1];
    }
    cv::Mat image = cv::imread( imageName );
    if (image.empty()) {
        std::cout << "Could not open or find the image\n";
        return 1;
    }

    // auto start = std::chrono::high_resolution_clock::now();
    // for( int y = 1; y < image.rows - 1; y++ ) {
    //     for( int x = 1; x < image.cols - 1; x++ ) {
           
    //     }
    // }
    // auto end = std::chrono::high_resolution_clock::now();

    // std::chrono::duration<double> elapsed = end - start;
    // std::cout << "Seq Img processing time: " << elapsed.count() << " seconds\n";

    std::cout << "Image loaded successfully!\n";
    std::cout << "Width: " << image.cols << "\n";
    std::cout << "Height: " << image.rows << "\n";
    std::cout << "Channels: " << image.channels() << "\n";

    cv::Mat gray = BasicStats::toGrayscale(image);
    BrightnessStats stats = BasicStats::computeBrightnessStats(gray);
    std::vector<int> buckets = BasicStats::computeHistogram(gray);

    int totalPixels = gray.rows * gray.cols;
    double entropy = BasicStats::computeEntropy(buckets, totalPixels);
    EdgeStats edgeStats = EdgeAnalysis::computeEdgeStats(gray);

    cv::Mat laplacian = EdgeAnalysis::laplacianFilter(gray);

    // Convert signed Laplacian values to absolute values
    cv::Mat laplacianAbs = cv::abs(laplacian);

    // Normalize values into 0-255 so the image is viewable
    cv::Mat laplacianVisual;
    cv::normalize(laplacianAbs, laplacianVisual, 0, 255, cv::NORM_MINMAX);

    // Convert from CV_64F to CV_8U because imwrite expects normal image format
    laplacianVisual.convertTo(laplacianVisual, CV_8U);

    // Save the output image
    cv::imwrite("../results/laplacian_output.jpg", laplacianVisual);

    std::cout << "Saved Laplacian image to ../results/laplacian_output.jpg\n";

    // Canny edge detection output
    cv::Mat canny = EdgeAnalysis::cannyEdge(gray, 100.0, 200.0);
    cv::imwrite("../results/canny_output.jpg", canny);
    int cannyEdges = cv::countNonZero(canny);
    double cannyEdgeDensity = static_cast<double>(cannyEdges) / totalPixels;
    std::cout << "Saved Canny image to ../results/canny_output.jpg\n";
    std::cout << "Canny Edge Density: " << cannyEdgeDensity << "\n";


    std::cout << "\nBrightness Stats\n";
    std::cout << "Average: " << stats.average << "\n";
    std::cout << "Min: " << stats.min << "\n";
    std::cout << "Max: " << stats.max << "\n";
    std::cout << "Total: " << totalPixels << "\n";
    std::cout << "Entropy: " << entropy << "\n";

    std::cout << "\nEdge Stats\n";
    std::cout << "Edge Density: " << edgeStats.edgeDensity << "\n";
    std::cout << "Average Gradient: " << edgeStats.averageGradient << "\n";
    std::cout << "Sharpness: " << edgeStats.sharpness << "\n";
    return 0;
}