#include <iostream>
#include <string>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

int main(){

    // Load the card image
    std::string path = "../Resources/shapes.png";
    cv::Mat image = cv::imread(path);
    cv::Mat image_HSV;
    cv::Mat mask;   // General name: mask of the detected color shape

    // Convert the image to HSV format
    cv::cvtColor(image, image_HSV, cv::COLOR_BGR2HSV);

    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;     // Default max values of hue saturation and value (HSV model)

    // Create window trackbar to choose the color of choice
    // You can find the color range of choice from this trackbar and substitute the value in the above hmin,max etc.
    // e.g. to show only the red colors, we can put lowerrange (1,175,235) and upperrange (179, 226, 255) on the slider GUI and check
    cv::namedWindow("ColorPicker");
    cv::createTrackbar("HueMin", "ColorPicker", &hmin, 179);
    cv::createTrackbar("HueMax", "ColorPicker", &hmax, 179);
    cv::createTrackbar("SatMin", "ColorPicker", &smin, 255);
    cv::createTrackbar("SatMax", "ColorPicker", &smax, 255);
    cv::createTrackbar("ValMin", "ColorPicker", &vmin, 255);
    cv::createTrackbar("ValMax", "ColorPicker", &vmax, 255);

    while (true) {          // Wrap around a while loop when using a trackbar
        // Detect the color of choice
        cv::Scalar lower_range(hmin, smin, vmin);   // lower point of the range
        cv::Scalar upper_range(hmax, smax, vmax);   // lower point of the range
        cv::inRange(image_HSV, lower_range, upper_range, mask);
        
        cv::imshow("Image", image);
        cv::imshow("Image HSV", image);
        cv::imshow("Image Mask", mask);
        cv::waitKey(1);     // Change waitkey to 1 for the while loop
    }

    cv::destroyAllWindows();

    return 0;

}