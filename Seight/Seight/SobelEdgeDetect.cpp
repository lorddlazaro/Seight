#include "stdafx.h"
#include "SobelEdgeDetect.h"
//#include "defaultFilter.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

SobelEdgeDetect::SobelEdgeDetect()
{
}


SobelEdgeDetect::~SobelEdgeDetect(){
    
}

Mat SobelEdgeDetect::perform(Mat image)
{
    cout << "performing Sobel Edge Detection" << endl;
    
	Mat grad;
	grad = sobelEdge(image);
	//cv::imshow("Sobel", grad);
	//waitKey(0);
	return grad;

	//returns sobel edge detection; should be passed through gaussian blur, grayscaled and threshold
}

Mat SobelEdgeDetect::sobelEdge(Mat image){
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	Mat grad;
    
    //defaultFilter::perform(image);
    
    //cv::imshow("To be edge detected", image);
    //waitKey(0);
    
    cvtColor(image, image, CV_BGR2GRAY);
    //cv::imshow("gray", bw);
    
    cv::threshold(image, image, 200, 250, CV_THRESH_OTSU);
    //bitwise_not(image, image);
    //cv::imshow("threshold", bw);

	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y;
	/// Gradient X
	cv::Sobel(image, grad_x, ddepth, 1, 0, 1, scale, delta, BORDER_DEFAULT);
	//cv::imshow("Sobel X", grad_x);
	/// Gradient Y
	cv::Sobel(image, grad_y, ddepth, 0, 1, 1, scale, delta, BORDER_DEFAULT);
	//cv::imshow("Sobel Y", grad_y);

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    
    //change color of edge

	return grad;
}