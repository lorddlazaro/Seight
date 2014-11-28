#include "stdafx.h"
#include "HSVSegment.h"

using namespace std;
using namespace cv;

HSVSegment::HSVSegment()
{
}


HSVSegment::~HSVSegment()
{
}

Mat HSVSegment::perform(Mat image)
{
	//imshow("raw", image);
	//placeholder for HSV image
	Mat hsvImage;
	//Convert image to HSV
	cvtColor(image, hsvImage, CV_BGR2HSV);

	//imshow("HSV", hsvImage);

	//define range of green color in HSV
	Scalar green_min = Scalar(30, 70, 78);//30, 50, 50 (70, 100, 30);
	Scalar green_max = Scalar(80, 250, 255);//(115, 255, 50);

	Mat mask;
	
	inRange(hsvImage, green_min, green_max, mask);

	//imshow("mask", mask);

	Mat result;
	image.copyTo(result, mask);

	imwrite("image/result_HSV.JPG", result, vector < int > {0});

	//imshow("result", result);
	//waitKey(0);
	return result;
}
