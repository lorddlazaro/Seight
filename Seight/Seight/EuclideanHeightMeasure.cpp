//#include "stdafx.h"
#include <iostream>
#include "EuclideanHeightMeasure.h"
#include <vector>

using namespace std;
using namespace cv;

EuclideanHeightMeasure::EuclideanHeightMeasure()
{
}


EuclideanHeightMeasure::~EuclideanHeightMeasure()
{
}

float EuclideanHeightMeasure::perform(Mat image)
{
	cout << "in EuclideanHeightMeasure perform" << endl;

	int b, g, r;
	
	//unsigned char *input = (unsigned char*)(image.data);
	
	
    bool highestFound = false;//, lowestFound = false;
	
	int highx = 0, highy = 0, lowx = 0, lowy = 0;

	//cout << skeleton << endl;
	cvtColor(image, image, CV_GRAY2BGR);
	/*find highest point*/
	//imshow("SKEL", skeleton);
	// waitKey(0);
	//cout << "rows "; cout << skeleton.rows << endl;
	//cout << "cols "; cout << skeleton.cols << endl;

	//cout << "Looking for highest" << endl;
	//waitKey(0);
	for (int i = 0; i < image.rows && !highestFound; i++)
	{
		for (int j = 0; j < image.cols && !highestFound; j++)
		{
			//cout << skeleton.at<Vec3b>(i, j) << endl;
			Vec3b pixel = image.at<Vec3b>(i, j);
			//cout << "i" << i;
			//cout << "j" << j << endl;
			//waitKey(0);
			b = pixel.val[0];
			g = pixel.val[1];
			r = pixel.val[2];

			//cout << "r:" << r << " g:" << g << " b:" << b << endl;

			if (b == 255 && g == 255 && r == 255){
				//cout << "yes" << endl;
				highx = i;
				highy = j;
				highestFound = true;
				image.at<Vec3b>(i, j) = pixel;
				//cout << "r:" << r << " g:" << g << " b:" << b << endl;
				//cout << "highest found! " << i << " " << j << endl;
				//waitKey(0);
			}
			//else cout << "no" << endl;
		}
	}
	//cout << "Looking for lowest" << endl;
	//cout << "rows "; cout << skeleton.rows-1 << endl;
	//cout << "cols "; cout << skeleton.cols-1 << endl;
	//waitKey(0);

	/* Define Plant Base Point
	 * y = image height - 16 
	 * x = image width / 2 */
//	int y = image.rows - 1;
//	int x = image.cols / 2;
	/* x = image width / 2 */

	/*travel skeleton*/
	/*find lowest point*
	for (int i = image.rows - 1; i >= 0 && !lowestFound; i--)
	{
		for (int j = image.cols - 1; j >= 0 && !lowestFound; j--)
		{
			Vec3b pixel = image.at<Vec3b>(i, j);
			//cout << "i" << i;
			//cout << "j" << j << endl;
			b = pixel[0];
			g = pixel[1];
			r = pixel[2];
			//cout << "r:" << r << " g:" << g << " b:" << b << endl;
			if (b == 255 && g == 255 && r == 255){
				lowx = i;
				lowy = j;
				lowestFound = true;
				//cout << "r:" << r << " g:" << g << " b:" << b << endl;
				//cout << "lowest found! " << i << " " << j << endl;
				//waitKey(0);
			}
		}
	}
	**/

	//imshow("COLOR", skeleton);
	//waitKey(0);
	double length = EuclideanHeightMeasure::getDistance(lowx - highx, lowy - highy);
	//height = length / cmConversion; //convert to cm

	//cout << "height: " << height << endl;

	return length;
}

float EuclideanHeightMeasure::getDistance(float x, float y){
	float distance;

	distance = pow(x, 2) + pow(y, 2);
	distance = sqrt(distance);

	return distance;
}