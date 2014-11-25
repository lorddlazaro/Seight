#include "stdafx.h"
#include "SobelEdgeDetect.h"


SobelEdgeDetect::SobelEdgeDetect()
{
}


SobelEdgeDetect::~SobelEdgeDetect()
{
}

Mat SobelEdgeDetect::perform(Mat image)
{
	Mat grad;
	grad = sobelEdge(image);
	cv::imshow("Sobel", grad);
	waitKey(0);
	return grad;

	//returns sobel edge detection; should be passed through gaussian blur, grayscaled and threshold
}

Mat SobelEdgeDetect::sobelEdge(Mat bw){
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	Mat grad;

	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y;
	/// Gradient X
	cv::Sobel(bw, grad_x, ddepth, 1, 0, 1, scale, delta, BORDER_DEFAULT);
	//cv::imshow("Sobel X", grad_x);
	/// Gradient Y
	cv::Sobel(bw, grad_y, ddepth, 0, 1, 1, scale, delta, BORDER_DEFAULT);
	//cv::imshow("Sobel Y", grad_y);

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	return grad;
}