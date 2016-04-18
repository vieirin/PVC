#include "PointClickDistance.hpp"
#include <iostream>

int main(int argc, char** argv){


    cv::VideoCapture cap(1);
    cv::Mat distortionMat, intrinsicsMat;
    cv::Mat mapx, mapy, frame;
    std::string distortion = "Distortion.xml";
    std::string intrinsics = "Intrinsics.xml";

    cap >> frame;
    cv::FileStorage dstfs(distortion, cv::FileStorage::READ);
    dstfs["Distortion"] >> distortionMat;
    dstfs.release();

    cv::FileStorage intrfs(intrinsics, cv::FileStorage::READ);
    intrfs["Intrinsics"] >> intrinsicsMat;
    intrfs.release();

    cv::Mat emptyR;
    mapx.create(frame.size(), CV_32FC1);
    mapy.create(frame.size(), CV_32FC1);
    cv::initUndistortRectifyMap(intrinsicsMat, distortionMat, emptyR, intrinsicsMat,frame.size(), CV_32FC1, mapx, mapy);
    cv::namedWindow("remaped window", 1);
    while(true){
    	PointClickDistance windowClick("Raw Image");
    	windowClick.setframe(frame);
    	cv::imshow("Raw Image", frame);
    	cv::Mat img = frame.clone();
    	cv::remap(img, frame, mapx, mapy, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0, 0));
    	cv::imshow("Undistort Image", frame);
    	windowClick.gettingROI();
    	if (cv::waitKey(30) >= 30) break;
    	cap >> frame;
    }
    return 0;
}
