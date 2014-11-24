#ifndef IEdgeDetect_H
#define IEdgeDetect_H

//#include "stdafx.h"
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class IEdgeDetect
{
public:
	IEdgeDetect();
	~IEdgeDetect();
    Mat sobelEdge(Mat bw);
	virtual Mat perform(Mat img); //vector<int>
};

#endif
