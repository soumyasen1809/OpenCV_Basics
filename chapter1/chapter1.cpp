#include <iostream>
#include <string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


int main(){

    // Display Images

    std::string path = "../Resources/land.jpg";   // Executed from the build directory
    cv::Mat image = cv::imread(path);
    cv::imshow("Image_Test", image);    // image will open and close instantly now. Need waitkey for the image to stay open (milliseconds)
    cv::waitKey(0);     // waitkey (0) is special - means keep window open forever

    
    // Display Videos

    // std::string path_video = "../Resources/test_video.mp4";
    // cv::VideoCapture video_object(path_video);
    // cv::Mat img_show;

    // while(true){
    //     video_object.read(img_show);
    //     cv::imshow("Video_Test", img_show);
    //     cv::waitKey(20);
    // }
    // Note: At the end there will be an error since there are no frames to show


    // Display Webcam capture

    cv::VideoCapture cam_object(0);       // Use camera id (0 is single camera present)
    cv::Mat cam_img_show;

    while(true){
        cam_object.read(cam_img_show);
        cv::imshow("Webcam_Test", cam_img_show);
        cv::waitKey(2);
    }
    // Note: At the end on closing the cam windows, a new window appears (infinite loop)


    return 0;
}