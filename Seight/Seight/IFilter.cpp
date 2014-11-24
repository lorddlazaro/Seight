//#include "stdafx.h"
#include "IFilter.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

IFilter::IFilter()
{
}


IFilter::~IFilter()
{
}

Mat IFilter::perform(Mat img)
{
    cv::GaussianBlur(img, img, Size(3,3), 0, 0, BORDER_DEFAULT );
    imshow("Gaussian Blur", img);
    
    cv::Mat bw;
    cv::cvtColor(img, bw, CV_BGR2GRAY);
    //cv::imshow("gray", bw);
    
    cv::threshold(bw, bw, 200, 250, CV_THRESH_OTSU);
    
    return bw;
    
    //bw would be the input for skeletonization and edge detection
}