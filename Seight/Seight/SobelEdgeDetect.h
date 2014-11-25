#pragma once

#ifndef SobelEdgeDetect_H
#define SobelEdgeDetect_H

#include "IEdgeDetect.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class SobelEdgeDetect : public IEdgeDetect
{
public:
	SobelEdgeDetect();
	~SobelEdgeDetect();
	Mat perform(Mat image);
	Mat sobelEdge(Mat bw);
};

#endif SobelEdgeDetect_H