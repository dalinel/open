#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"

int main(int argc, char **argv)
{
    ros::init(argc,argv,"color");
    ros::NodeHandle n;


    cv::VideoCapture cap(0);
    if(!cap.isOpened())
        return 1;

    while(ros::ok()){
        cv::Mat frame;
        cv::Mat frameGray;
        cv::Mat imgKeypoints;
        std::vector<cv::KeyPoint> keypoints;

        cv::Ptr<cv::FeatureDetector> detector = cv::FeatureDetector::create("STAR");

        cap >> frame;
        cv::imshow("webcam",frame);
        if(cv::waitKey(30) >= 0) break;

        cv::cvtColor( frame, frameGray, CV_BGR2GRAY );
        cv::imshow("webcamGray",frameGray);


        detector->detect( frameGray, keypoints);

        cv::drawKeypoints( frameGray, keypoints, imgKeypoints , cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT );
        cv::imshow("webcamKey",imgKeypoints);



    }

}
