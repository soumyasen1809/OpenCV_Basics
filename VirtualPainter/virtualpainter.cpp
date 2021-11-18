#include <iostream>
#include <string>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>


cv::VideoCapture cam_object(0);
cv::Mat frames;

std::vector<std::vector<int>> HSV_min = {{103,200,106}};
std::vector<std::vector<int>> HSV_max = {{179,255,209}};
std::vector<cv::Scalar> Color = {{255,0,0}};
std::vector<std::string> ColorName = {"Blue"};

std::vector<std::vector<int>> drawingPoints;


cv::Point detectContours(cv::Mat image_input){
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    
    // Find and draw the contours
    cv::findContours(image_input, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> contour_poly(contours.size());
    std::vector<cv::Rect> boundary_rect(contours.size());
    cv::Point marker_point(0,0);

    // Get the area of all the contours
    for (auto i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);

        // Store the contour points and label the shapes
        if (area > 500) {
            cv::approxPolyDP(contours[i], contour_poly[i], 7, true);        // Played around to find 7 as the precision
            boundary_rect[i] = cv::boundingRect(contour_poly[i]);
            cv::drawContours(frames, contours, i, cv::Scalar(210,12,120), 2);
            cv::rectangle(frames, boundary_rect[i].tl(), boundary_rect[i].br(), cv::Scalar(10,12,10), 3);
            
            marker_point.x = boundary_rect[i].x;
            marker_point.y = boundary_rect[i].y;

        }
        
    }

    return marker_point;

}



std::vector<std::vector<int>> findColor(cv::Mat image_input){
    cv::Mat img_HSV, mask;
    cv::cvtColor(image_input, img_HSV, cv::COLOR_BGR2HSV);

    for (auto i = 0; i < HSV_min.size(); i++) {
        cv::Scalar lower_range(HSV_min[i][0], HSV_min[i][1], HSV_min[i][2]);   // lower point of the range
        cv::Scalar upper_range(HSV_max[i][0], HSV_max[i][1], HSV_max[i][2]);   // lower point of the range

        cv::inRange(img_HSV, lower_range, upper_range, mask);
        // cv::imshow(std::to_string(i), mask);
        cv::Point markerpoint = detectContours(mask);

        drawingPoints.push_back({markerpoint.x, markerpoint.y, i});
    }

    return drawingPoints;
}



void paint(std::vector<std::vector<int>> drawingPoints, std::vector<cv::Scalar> Color){
    for (auto i = 0; i < drawingPoints.size(); i++) {
        cv::circle(frames, cv::Point(drawingPoints[i][0], drawingPoints[i][1]), 5, Color[drawingPoints[i][2]], cv::FILLED);
    }
    
}


int main(){
    
    //////// CODE to pick the color using a trackbar ////////

    // cv::Mat img_HSV, mask;
    // int hmin = 0, smin = 0, vmin = 0;
    // int hmax = 179, smax = 255, vmax = 255;     // Default max values of hue saturation and value (HSV model)

    // // Create window trackbar to choose the color of choice
    // // You can find the color range of choice from this trackbar and substitute the value in the above hmin,max etc.
    // // e.g. to show only the red colors, we can put lowerrange (1,175,235) and upperrange (179, 226, 255) on the slider GUI and check
    // cv::namedWindow("ColorPicker");
    // cv::createTrackbar("HueMin", "ColorPicker", &hmin, 179);
    // cv::createTrackbar("HueMax", "ColorPicker", &hmax, 179);
    // cv::createTrackbar("SatMin", "ColorPicker", &smin, 255);
    // cv::createTrackbar("SatMax", "ColorPicker", &smax, 255);
    // cv::createTrackbar("ValMin", "ColorPicker", &vmin, 255);
    // cv::createTrackbar("ValMax", "ColorPicker", &vmax, 255);


    // while (true) {
    //     cam_object.read(frames);

    //     cv::cvtColor(frames, img_HSV, cv::COLOR_BGR2HSV);
    //     cv::Scalar lower_range(hmin, smin, vmin);   // lower point of the range
    //     cv::Scalar upper_range(hmax, smax, vmax);   // lower point of the range
    //     cv::inRange(img_HSV, lower_range, upper_range, mask);

    //     cv::imshow("Color Picker", mask);
    //     cv::waitKey(1);
    // }

    // cv::destroyAllWindows();

    //////// *************************************** ////////

    // Colors picked: Hmin: 103, Hmax: 179, Smin: 200, Smax: 255, Vmin: 106, Vmax: 209

    while (true) {
        cam_object.read(frames);

        drawingPoints = findColor(frames);
        paint(drawingPoints, Color);

        cv::imshow("Painter", frames);
        cv::waitKey(1);
    }

    return 0;

}