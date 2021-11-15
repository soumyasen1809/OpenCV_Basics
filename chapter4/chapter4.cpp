#include <iostream>
#include <string>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

int main(){
    // Create a blank image
    cv::Mat image(512, 512, CV_8UC3, cv::Scalar(220,100,200));    // Use Scalar(B,G,R) to define the color

    // Create shapes and text on the image
    cv::circle(image, cv::Point(200,300), 100, cv::Scalar(20,170,10), 4);
    cv::rectangle(image, cv::Point(120, 210), cv::Point(210, 120), cv::Scalar(200,90,80), cv::FILLED);
    cv::putText(image, "OpenCV4", cv::Point(340,321), cv::FONT_HERSHEY_SCRIPT_COMPLEX, 1.2, cv::Scalar(34,12,234), 0.5);
    

    cv::imshow("Image_Test", image);
    cv::waitKey(0);

    return 0;

}