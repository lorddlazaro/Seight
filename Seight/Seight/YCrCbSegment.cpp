#include "stdafx.h"
#include "YCrCbSegment.h"


YCrCbSegment::YCrCbSegment()
{
}

Mat YCrCbSegment::perform(Mat image)
{
	//imshow("raw", image);
	//placeholder for YCrCb image
	Mat YCrCbImage;
	//Convert image to YCrCb
	cvtColor(image, YCrCbImage, CV_BGR2YCrCb);

	//hsv1=30,50,50 | 115,255,50
	//hsv2=30,70,70 | 80,250,255
	//hsv3=

	//imshow("YCrCb", YCrCbImage);

	//define range of green color in HSV
	Scalar green_min = Scalar(0, 0, 0);//30, 50, 50 (70, 100, 30);
	Scalar green_max = Scalar(60, 255, 255);//(115, 255, 50);

	Mat mask;

	inRange(YCrCbImage, green_min, green_max, mask);

	//imshow("mask", mask);

	Mat result;
	image.copyTo(result, mask);

	imwrite("image/result_YCrCb.JPG", result, vector < int > {0});

	//imshow("result", result);
	//waitKey(0);
	return result;
}

YCrCbSegment::~YCrCbSegment()
{
}
