#include "stdafx.h"
#include "defaultPerspectiveCorrect.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

defaultPerspectiveCorrect::defaultPerspectiveCorrect()
{
}


defaultPerspectiveCorrect::~defaultPerspectiveCorrect()
{
}

Mat defaultPerspectiveCorrect::perform(Mat image)
{
	//cout << "performing Perspective Correction" << endl;
	return image;
}
