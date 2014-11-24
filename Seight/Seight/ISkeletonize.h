#ifndef ISkeletonize_H
#define ISkeletonize_H

//#include "stdafx.h"
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class ISkeletonize
{
public:
	ISkeletonize();
	~ISkeletonize();
	Mat perform(Mat img); //vector<int>
    void thinningIteration(Mat& im, int iter);
    void thinning(Mat& im);
};

#endif