#include<iostream>
#include<string>
#include<vector>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>


int main(){
    cv::VideoCapture webcam(0);
    cv::Mat image;

    while (true) {
        webcam.read(image);
        
        // Load the licenseplate cascade
        cv::CascadeClassifier plate_cascade;
        plate_cascade.load("../Resources/haarcascade_russian_plate_number.xml");

        // Detect the licenseplate
        std::vector<cv::Rect> plate_rect;
        plate_cascade.detectMultiScale(image, plate_rect, 1.1, 3);

        // Draw the rectangle
        for (auto i = 0; i < plate_rect.size(); i++) {
            cv::rectangle(image, plate_rect[i].tl(), plate_rect[i].br(), cv::Scalar(220,120,20), 3);
        }
        

        cv::imshow("LicensePlate", image);
        cv::waitKey(1);
    }
    
    return 0;
}