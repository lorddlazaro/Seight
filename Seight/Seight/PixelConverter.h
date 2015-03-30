//#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class PixelConverter
{
public:
	PixelConverter();
	~PixelConverter();
	int getPixelConversionCentimeter(Mat image);
    double convertImagePixelstoCentimeter(Mat marker, int heightPixel);
};

