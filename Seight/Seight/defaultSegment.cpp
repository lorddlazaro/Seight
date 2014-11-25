#include "stdafx.h"
#include "defaultSegment.h"

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

defaultSegment::defaultSegment()
{
}


defaultSegment::~defaultSegment()
{
}

Mat defaultSegment::perform(Mat image_)
{
	cout << "perform segmentation" << endl;

	Mat color_image = image_;

	Mat image;
	cvtColor(color_image, image, CV_BGR2GRAY);	//convert image to gray
	
	Mat binary;
	threshold(image, binary, 140, 255, cv::THRESH_BINARY); // convert image to binary
	bitwise_not(binary, binary);
	
	Mat result;
	color_image.copyTo(result, binary);
	showImage("result", result);

	imwrite("image/result.JPG", result, vector < int > {0});

	return result;
}

void defaultSegment::showImage(string name, Mat image)
{
	namedWindow(name, WINDOW_AUTOSIZE);// Create a window for display.
	imshow(name, image);
	waitKey(3000);
}