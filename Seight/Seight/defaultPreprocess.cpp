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

Mat defaultPreprocess::perform(Mat image)
{
	/*HISTOGRAM EQUALIZATION*/
	cout << "default preprocessing" << endl;
	
	Mat hsv;
	//imshow("image", image);
	cvtColor(image, hsv, CV_BGR2YCrCb);

	vector<Mat> channels;
	split(hsv, channels);

	Mat result;
	equalizeHist(channels[0], channels[0]);
	//equalizeHist(channels[1], channels[1]);
	//equalizeHist(channels[2], channels[2]);
	merge(channels, hsv);
	cvtColor(hsv, result, CV_YCrCb2BGR);
	imshow("h", hsv);
	imshow("im", image);
	imshow("r", result);
	waitKey(0);

	//imshow("result", result);
	//waitKey(0);

	return result;
}