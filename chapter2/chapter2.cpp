#include <iostream>
#include <string>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

int main(){
    std::string path = "../Resources/lena.png";
    cv::Mat image = cv::imread(path);

    // Functions on the image
    cv::Mat img_gray, img_gauss, img_canny, img_dia, img_ero;

    cv::cvtColor(image, img_gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(image, img_gauss, cv::Size(5,5), 10, 0);
    
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::Canny(img_gauss, img_canny, 50, 50);    // Practice: Blurr the image first a bit before passing through canny edge detection
    cv::dilate(img_canny, img_dia, kernel);     // Dialating/increasing the thickness of the lines in the canny image
    cv::erode(img_dia, img_ero, kernel);    // Eroding the thick lines obtained by dialating

    
    // Display the images
    cv::imshow("Image_Test", image);
    cv::imshow("Image_Gray", img_gray);
    cv::imshow("Image_Blur", img_gauss);
    cv::imshow("Image_Canny", img_canny);
    cv::imshow("Image_Dialate", img_dia);
    cv::imshow("Image_Erode", img_ero);
    cv::waitKey(0);


    return 0;

}