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
	
	//showImage("image", image);
	
	Mat binary;
	threshold(image, binary, 140, 255, cv::THRESH_BINARY); // convert image to binary
	bitwise_not(binary, binary);
	//showImage("binary", binary);

	auto const structure = getStructuringElement(MORPH_ELLIPSE,
		Size(1, 1));
	Mat fore_ground;
	erode(binary, fore_ground, structure, Point(-1, -1), 1);

	showImage("fore_ground", fore_ground);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(fore_ground, contours, CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_NONE);
	//remove_contours(contours, 8000, 80000);
	fore_ground.setTo(0);
	cv::drawContours(fore_ground, contours, -1, cv::Scalar(255), CV_FILLED);

	cv::Mat back_ground;
	cv::dilate(binary, back_ground, structure, cv::Point(-1, -1), 2);
	cv::threshold(back_ground, back_ground, 1, 120, cv::THRESH_BINARY_INV);

	showImage("background", back_ground);

	//cv::Mat markers = back_ground + fore_ground;
	//Mat markers = addMatrices(back_ground, fore_ground);
	Mat markers;
	cv::add(back_ground, fore_ground, markers);
	cout << back_ground.rows << endl;
	cout << back_ground.cols << endl;
	showImage("markers", markers);
	cv::Mat mask;
	markers.convertTo(mask, CV_32S);
	//showImage("from markers", mask);
	cv::watershed(color_image, mask);
	//showImage("watershed", mask);
	mask.convertTo(mask, CV_8U);
	//showImage("from mask", mask);
	cv::threshold(mask, mask, 150, 200, CV_THRESH_BINARY);

	//showImage("thresh mask", mask);

	cv::Mat result;
	color_image.copyTo(result, mask);

	//showImage("result", result);
	imwrite("image/result.JPG", result, vector < int > {0});

	return result;
}

void defaultSegment::showImage(string name, Mat image)
{
	namedWindow(name, WINDOW_AUTOSIZE);// Create a window for display.
	imshow(name, image);
	waitKey(3000);
}

Mat defaultSegment::addMatrices(Mat image1, Mat image2)
{
	Mat sum;

	for (int i = image1.rows/2; i < image1.rows; i++)
	{
		for (int j = image1.cols*0.3; j < image1.cols*0.7; j++)
		{
			sum.at<uchar>(i, j) = image1.at<uchar>(i, j) + image2.at<uchar>(i, j);
		}
	}

	namedWindow("SUM", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("SUM", sum);
	waitKey(3000);

	return sum;
}

void defaultSegment::remove_contours(vector<vector<Point>>&contours,
	double cmin, double cmax)
{
	auto it = partition(std::begin(contours), end(contours),
		[=](vector<Point> const &data)
	{
		auto const size = contourArea(data);
		return !(size < cmin || size > cmax);
	});
	contours.erase(it, end(contours));
}