#ifndef IPreprocess_H
#define IPreprocess_H

////#include "stdafx.h"
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class IPreprocess
{
public:
	IPreprocess();
	~IPreprocess();
	virtual Mat perform(Mat image);
};

#endif