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
	cout << "default preprocessing" << endl;

	return image;
}