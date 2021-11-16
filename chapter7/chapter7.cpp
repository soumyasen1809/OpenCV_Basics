#include <iostream>
#include <string>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

void getContour(cv::Mat image_input, cv::Mat image_output){
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    
    // Find and draw the contours
    cv::findContours(image_input, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(image_output, contours, -1, cv::Scalar(210,12,120), 2);    // Note contour id = -1 means all the contours are drawn

    std::vector<std::vector<cv::Point>> contour_poly(contours.size());
    std::vector<cv::Rect> boundary_rect(contours.size());

    // Get the area of all the contours
    for (auto i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        std::cout << "Area for contour " << i << " is: " << area << std::endl;

        // Store the contour points and label the shapes
        cv::approxPolyDP(contours[i], contour_poly[i], 7, true);        // Played around to find 7 as the precision
        boundary_rect[i] = cv::boundingRect(contour_poly[i]);

        std::cout << "Num of sides of the polygon: " << contour_poly[i].size() << std::endl;
        int num_corners = contour_poly[i].size();
        if (num_corners == 3) {
            cv::putText(image_output, "Triangle", boundary_rect[i].tl(), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.7, cv::Scalar(100,100,100), 0.8);
        }
        else if (num_corners == 4) {
            // Check if square or rectangle.
            // For square width == height, but we can't use == because of doubles used. Hence we define a range 0.9 to 1.1
            if (((double)boundary_rect[i].width/(double)boundary_rect[i].height < 1.1) && ((double)boundary_rect[i].width/(double)boundary_rect[i].height > 0.9)) {
                cv::putText(image_output, "Square", boundary_rect[i].tl(), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.7, cv::Scalar(100,100,100), 0.8);
            }
            else{
                cv::putText(image_output, "Rectangle", boundary_rect[i].tl(), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.7, cv::Scalar(100,100,100), 0.8);
            }
        }
        else if (num_corners == 5) {
            cv::putText(image_output, "Pentagon", boundary_rect[i].tl(), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.7, cv::Scalar(100,100,100), 0.8);
        }
        else if (num_corners > 5) {
            cv::putText(image_output, "Circle", boundary_rect[i].tl(), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.7, cv::Scalar(100,100,100), 0.8);
        }
        

        // If we want contours only for shapes above specified area (say 7000)
        // if (area > 7000) {
        //     cv::drawContours(image_output, contours, i, cv::Scalar(210,12,120), 2);    // Note contour id = -1 means all the contours are drawn
        // }

        // cv::drawContours(image_output, contour_poly, i, cv::Scalar(53, 51, 91), 1);     // Uncomment: see the contours for the fitted polygon
        
    }
    
}

int main(){

    // Load the image
    std::string path = "../Resources/shapes.png";
    cv::Mat image = cv::imread(path);
    cv::Mat image_gray, image_gauss, image_canny, image_dia;

    // Convert the image and apply Canny edge detection
    cv::cvtColor(image, image_gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(image_gray, image_gauss, cv::Size(5,5), 10, 0);
    cv::Canny(image_gauss, image_canny, 50, 50);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::dilate(image_canny, image_dia, kernel);     // dialating the edges a bit to get a better edge detection

    // Calling function to detect contours
    getContour(image_dia, image);

    cv::imshow("Image", image);
    cv::waitKey(0);

    return 0;

}