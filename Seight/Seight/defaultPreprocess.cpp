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
	
	Mat ycrcb;
	//imshow("image", image);
	cvtColor(image, ycrcb, CV_BGR2YCrCb);

	vector<Mat> channels;
	split(ycrcb, channels);

	equalizeHist(channels[0], channels[0]);

	Mat result;
	merge(channels, ycrcb);

	cvtColor(ycrcb, result, CV_YCrCb2BGR);

	//imshow("result", result);
	//waitKey(0);

	return result;
}