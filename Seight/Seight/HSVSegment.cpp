#include "stdafx.h"
#include "HSVSegment.h"

using namespace std;
using namespace cv;

HSVSegment::HSVSegment()
{
}


HSVSegment::~HSVSegment()
{
}

int minH = 25;
int minS = 215;
int minV = 55;
int maxH = 55;
int maxS = 255;
int maxV = 255;

void HSVSegment::setValues(vector<int> values)
{
    minH = values[0];
    minS = values[1];
    minV = values[2];
    maxH = values[3];
    maxS = values[4];
    maxV = values[5];
}

Mat HSVSegment::perform(Mat image)
{
	//imshow("raw", image);
	//placeholder for HSV image
	Mat hsvImage;
	//Convert image to HSV
	cvtColor(image, hsvImage, CV_BGR2HSV);
	
	//hsv1=30,50,50 | 115,255,50
	//hsv2=30,70,70 | 80,250,255
	//hsv3=
    
    vector<int> values;
    values.push_back(15);//minH
    values.push_back(35);//minS
    values.push_back(40);//minV
    values.push_back(70);//maxH
    values.push_back(250);//maxS
    values.push_back(240);//maxV
    
    setValues(values);
	//imshow("HSV", hsvImage);

	//define range of green color in HSV
	Scalar green_min = Scalar(minH, minS, minV);//0, 45, 10);//30, 50, 50 (70, 100, 30);
	Scalar green_max = Scalar(maxH, maxS, maxV);//135, 255, 100);//(115, 255, 50);

	Mat mask;
	
	inRange(hsvImage, green_min, green_max, mask);
    
    //imshow("mask", mask);

	Mat result;
	image.copyTo(result, mask);

	imwrite("image/result_HSV.JPG", result, vector < int > {0});

	//imshow("result", result);
	//waitKey(0);
	return result;
}
