#include "stdafx.h"
#include <iostream>
#include "defaultPreprocess.h"

using namespace std;
using namespace cv;

defaultPreprocess::defaultPreprocess()
{
}


defaultPreprocess::~defaultPreprocess()
{
}

Mat defaultPreprocess::perform(Mat raw_image)
{
	/*HISTOGRAM EQUALIZATION*/
	cout << "default preprocessing" << endl;

	//Crop Image
	Rect rect_roi = Rect(0, 0, 240, 467);
	Mat image = raw_image(rect_roi);

	Mat hsv;
	//imshow("image", image);
	cvtColor(image, hsv, CV_BGR2HSV);

	vector<Mat> channels;
	split(hsv, channels);

	Mat result;
	equalizeHist(channels[0], channels[0]);
	//equalizeHist(channels[1], channels[1]);
	//equalizeHist(channels[2], channels[2]);
	merge(channels, hsv);
	cvtColor(hsv, result, CV_HSV2BGR);
	//imshow("h", hsv);
	//imshow("im", image);
	//imshow("r", result);
	//waitKey(0);

	//imshow("result", result);
	//waitKey(0);

	return result;
}