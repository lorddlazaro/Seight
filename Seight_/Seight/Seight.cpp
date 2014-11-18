/**
*	SEIGHT
*	by Seight Team
*	Constantino, Gonzales, Lazaro, Serrano
*/

/*Visual Studio*/

#include "stdafx.h"
/**
* Code for thinning a binary image using Zhang-Suen algorithm.
*/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

using namespace cv;
using namespace std;

/**
* Perform one thinning iteration.
* Normally you wouldn't call this function directly from your code.
*
* @param  im    Binary image with range = 0-1
* @param  iter  0=even, 1=odd
*/
void thinningIteration(cv::Mat& im, int iter)
{
	cv::Mat marker = cv::Mat::zeros(im.size(), CV_8UC1);

	for (int i = 1; i < im.rows - 1; i++)
	{
		for (int j = 1; j < im.cols - 1; j++)
		{
			uchar p2 = im.at<uchar>(i - 1, j);
			uchar p3 = im.at<uchar>(i - 1, j + 1);
			uchar p4 = im.at<uchar>(i, j + 1);
			uchar p5 = im.at<uchar>(i + 1, j + 1);
			uchar p6 = im.at<uchar>(i + 1, j);
			uchar p7 = im.at<uchar>(i + 1, j - 1);
			uchar p8 = im.at<uchar>(i, j - 1);
			uchar p9 = im.at<uchar>(i - 1, j - 1);

			int A = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
				(p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
				(p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
				(p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
			int B = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
			int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
			int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

			if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
				marker.at<uchar>(i, j) = 1;
		}
	}

	im &= ~marker;
}

/**
* Function for thinning the given binary image
*
* @param  im  Binary image with range = 0-255
*/
void thinning(cv::Mat& im)
{
	im /= 255;

	cv::Mat prev = cv::Mat::zeros(im.size(), CV_8UC1);
	cv::Mat diff;

	do {
		thinningIteration(im, 0);
		thinningIteration(im, 1);
		cv::absdiff(im, prev, diff);
		im.copyTo(prev);
	} while (cv::countNonZero(diff) > 0);

	im *= 255;
}

/**
* This is an example on how to call the thinning function above.
*/
int main()
{
	cv::Mat src = cv::imread("crop1.jpg");
	if (src.empty())
		return -1;
	cv::Mat bw;
	cv::cvtColor(src, bw, CV_BGR2GRAY);
	cv::imshow("gray", bw);
	cv::Mat canny;
	cv::Canny(bw, canny, 300, 300, 3);
	cv::imshow("Canny", canny);
	cv::threshold(bw, bw, 200, 250, CV_THRESH_OTSU);
	bitwise_not(bw, bw);
	cv::imshow("threshold", bw);
	thinning(bw);
	cv::imshow("skeletonization", bw);

	
/*	int totalPix = bw.rows * bw.cols;
	int whitePix = countNonZero(bw);
	cout << whitePix << "total is" << totalPix;
	Point pt1 = (50, 10);
	Point pt2 = (100, 100);

	cv::Mat img_rgb(bw.size(), CV_8UC3);

	cv::cvtColor(bw, img_rgb, CV_GRAY2RGB);
	line(bw, pt1, pt2, CV_RGB(255, 0, 0), 3, 8, 0);
	imshow("line", bw);
	/**vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;

	findContours(bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_L1, Point());
	Mat bwDraw = Mat::zeros(bw.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++){
		drawContours(bw, contours, -1, Scalar(200, 0, 0), 1, 8, hierarchy, 2, Point());
		line( bw, Point(i, 0), Point(0,0), CV_RGB(255, 0, 0), 1, 8, 0);
	}
	*/

	//cv::imshow("src", src);
	cv::waitKey(0);

	return 0;
}