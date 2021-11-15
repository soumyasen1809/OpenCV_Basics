#include <iostream>
#include <string>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

int main(){
    std::string path = "../Resources/lena.png";
    cv::Mat image = cv::imread(path);

    // Resizing image
    cv::Mat image_resized;
    cv::resize(image, image_resized, cv::Size(), 0.5, 0.5);     // resized by a scaling factor 0.5,0.5
    // cv::resize(image, image_resized, cv::Size((image.rows)/5, (image.cols)/5));     // resizing by size (rows and columns)

    // Crop images
    cv::Rect crop_window(150,150, 220, 250);        // trial and error the values (X,Y) of the starting point and (width (along X), height (along Y below direction))
    cv::Mat image_crop = image(crop_window);

    
    // Display the images
    cv::imshow("Image_Test", image);
    cv::imshow("Image resized", image_resized);
    cv::imshow("Image cropped", image_crop);
    cv::waitKey(0);


    return 0;

}