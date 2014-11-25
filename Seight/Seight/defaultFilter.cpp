#include "stdafx.h"
#include "defaultFilter.h"
#include <iostream>

using namespace std;

defaultFilter::defaultFilter()
{
}


defaultFilter::~defaultFilter()
{
}

void defaultFilter::perform(Mat image)
{
	cout << "perfom image filtering" << endl;
    
    cv::GaussianBlur(image, image, Size(3,3), 0, 0, BORDER_DEFAULT );
}