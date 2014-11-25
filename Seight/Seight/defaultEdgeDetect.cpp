#include "stdafx.h"
#include "defaultEdgeDetect.h"
#include <iostream>

using namespace std;

defaultEdgeDetect::defaultEdgeDetect()
{
}


defaultEdgeDetect::~defaultEdgeDetect()
{
}

Mat src_gray; Mat src; Mat result;
int thresh = 50;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int value, void *userdata)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8, hierarchy, 0, Point());
	}

	/// Show in a window
	//namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	//imshow("Contours", drawing);

	imwrite("image/edgeDetect_Draw.JPG", drawing, vector < int > {0});

	//drawing.copyTo(result, src);
	result = src + drawing;
	imwrite("image/result_Canny.JPG", result, vector < int > {0});
}


Mat defaultEdgeDetect::perform(Mat image)
{
	cout << "perform edge detection" << endl;
	src = image;
	/// Convert image to gray and blur it
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// Create Window
	//char* source_window = "Source";
	//namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	//imshow(source_window, src);

	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	//waitKey(0);

	return result;
}


