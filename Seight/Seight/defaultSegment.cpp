#include "stdafx.h"
#include "defaultSegment.h"

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using ContoursType = std::vector<std::vector<cv::Point> >;

defaultSegment::defaultSegment()
{
}


defaultSegment::~defaultSegment()
{
}

Mat defaultSegment::perform(Mat image_)
{
	//cout << "perform segmentation" << endl;

	Mat color_image = image_;
	
	cv::Mat image;
	cv::cvtColor(color_image, image, CV_BGR2GRAY);

	cv::Mat binary;
	cv::threshold(image, binary, 140, 255, cv::THRESH_BINARY);
	bitwise_not(binary, binary);
	imshow("thresh", binary);
	//cv::imwrite("binaryOrigin" + num + ".png", binary);

	auto const structure = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
	cv::erode(binary, binary, structure);
	cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, structure);
	cv::imshow("binary", binary);
	//cv::imwrite("binaryMorph" + num + ".png", binary);

	ContoursType contours;
	cv::findContours(binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cv::Mat mask(image.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(mask, contours, -1, cv::Scalar(0), CV_FILLED);
	//cv::imwrite("rawContours" + num + ".png", mask);
	imshow("mask", mask);
	//defaultSegment::remove_contours(contours, 1000, 10000);
	mask.setTo(0);
	cv::drawContours(mask, contours, -1, cv::Scalar(255), CV_FILLED);
	imshow("contours", mask);
	cv::Mat result;
	//cv::imwrite("finalMask" + num + ".png", mask);
	color_image.copyTo(result, mask);

	cv::imshow("result", result);
	//cv::imwrite("result" + num + ".png", result);

	/**
	Mat binary;
	threshold(image, binary, 140, 255, THRESH_BINARY); // convert image to binary
	bitwise_not(binary, binary);

imshow("thresh", binary);
	auto const structure = getStructuringElement(MORPH_ELLIPSE,
		Size(2, 2));
	Mat fore_ground;
	erode(binary, fore_ground, structure, Point(-1, -1), 4);
imshow("fore_ground", fore_ground);
	vector<vector<Point>> contours;
	findContours(fore_ground, contours, CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_NONE);
	defaultSegment::remove_contours(contours, 500, 500);
	fore_ground.setTo(0);
	drawContours(fore_ground, contours, -1, Scalar(255), CV_FILLED);

	Mat back_ground;
	dilate(binary, back_ground, structure, Point(-1, -1), 4);
	threshold(back_ground, back_ground, 1, 128, THRESH_BINARY_INV);
imshow("bg",back_ground);

	Mat markers = back_ground + fore_ground; imshow("markers", markers);
	Mat mask;
	markers.convertTo(mask, CV_32S);
	watershed(color_image, mask);
	mask.convertTo(mask, CV_8U);
	threshold(mask, mask, 150, 255, CV_THRESH_BINARY);
	imshow("mask", mask);
	Mat result;
	color_image.copyTo(result, mask);

	imshow("result", result);

	imwrite("image/result.JPG", result, vector < int > {0});
	/**/
	return result;
}

void defaultSegment::remove_contours(std::vector<std::vector<cv::Point> > &contours, double cmin, double cmax)
{
	auto it = std::partition(std::begin(contours), std::end(contours), [=](std::vector<cv::Point> const &data)
	{
		auto const size = cv::contourArea(data);
		return !(size < cmin || size > cmax);
	});
	contours.erase(it, std::end(contours));
}

void defaultSegment::showImage(string name, Mat image)
{
	namedWindow(name, WINDOW_AUTOSIZE);// Create a window for display.
	imshow(name, image);
	waitKey(3000);
}