#include <iostream>
#include <string>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>


int main(){

    // Load the image
    std::string path = "../Resources/lena.png";
    cv::Mat image = cv::imread(path);

    // Load the cascade
    // Cascade: https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_default.xml
    cv::CascadeClassifier face_cascade;
    std::string path_xml = "../Resources/haarcascade_frontalface_default.xml";
    face_cascade.load(path_xml);

    // Detect faces
    std::vector<cv::Rect> rect;
    face_cascade.detectMultiScale(image, rect, 1.1, 3);

    // Draw rectangles around the faces
    for (auto i = 0; i < rect.size(); i++) {
        cv::rectangle(image, rect[i].tl(), rect[i].br(), cv::Scalar(32, 211, 91), 2);
    }
    

    cv::imshow("Image", image);
    cv::waitKey(0);

    return 0;

}