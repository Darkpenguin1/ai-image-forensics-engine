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