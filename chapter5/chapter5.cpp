#include <iostream>
#include <string>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

int main(){

    // Load the card image
    std::string path = "../Resources/cards.jpg";
    cv::Mat image = cv::imread(path);

    // Choose the corner points of the card
    cv::Point2f input_points[4] = {{110,218},{288,188},{155,480},{355,441}};
    cv::Point2f output_points[4] = {{0,0},{250,0},{0,350},{250,350}};     // assume width 400 and height 500 of the output image

    // Perspective transform
    cv::Mat warp_matrix = cv::getPerspectiveTransform(input_points,output_points);      // need to define src and dst as Point2f instead of Point
    cv::Mat image_warped;
    cv::warpPerspective(image,image_warped,warp_matrix,cv::Size(250,350));

    // Mark the corner points used for the transformation
    for (auto i = 0; i < 4; i++) {
        cv::circle(image, input_points[i], 10, cv::Scalar(130,220,110), cv::FILLED);
    }
    
    
    cv::imshow("Card Image", image);
    cv::imshow("Card Image Warp", image_warped);
    cv::waitKey(0);

    return 0;

}