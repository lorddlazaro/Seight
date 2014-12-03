#include "stdafx.h"
#include "PlantModeler.h"
#include <iostream>
#include <vector>

using namespace std;

void PlantModeler::processImage(Mat image) //PhenotypicData
{
    cout << "processing image" << endl;
    PlantModeler::correction->perform();
    Mat segmentedImage = PlantModeler::segmentation->perform(image);
    PlantModeler::imageFiltering->perform(segmentedImage);
    Mat edge = PlantModeler::edgeDetection->perform(segmentedImage);
    
    Mat skeleton = PlantModeler::skeletonization->perform(segmentedImage);
    //Vector<Point> img_points = PlantModeler::structure->perform(skeleton);
    PlantModeler::tillerCount->perform(edge, segmentedImage);
    PlantModeler::measureHeight(skeleton);
    //imshow("edge", edge);
    //waitKey(0);
    PlantModeler::tillerCount->perform(edge, segmentedImage);
    PlantModeler::measureHeight(skeleton);
    cout << "done processing" << endl;
}

PlantModeler::PlantModeler()
{
    cout << "PlantModeler constructed... " << endl;
}

PlantModeler::~PlantModeler(){
    
}

double PlantModeler::measureHeight(Mat skeleton)
{
	double pixelsIncm = 9;
	double height;
	double distance;
	int b, g, r;
	//unsigned char *input = (unsigned char*)(image.data);
	bool highestFound = false, lowestFound = false;
	int highx = 0, highy = 0, lowx = 0, lowy = 0;
	
	//cout << skeleton << endl;


	/*find highest point*/
	imshow("SKEL", skeleton);
	waitKey(0);
	cout << "rows "; cout << skeleton.rows << endl;
	cout << "cols "; cout << skeleton.cols << endl;

	cout << "Looking for highest" << endl;
	waitKey(0);
	for (int i = 0; i < skeleton.rows && !highestFound; i++)
	{
		for (int j = 0; j < skeleton.cols/3 && !highestFound; j++)
		{
			//cout << skeleton.at<Vec3b>(i, j) << endl;
			Vec3b pixel = skeleton.at<Vec3b>(i, j);
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
				skeleton.at<Vec3b>(i, j) = pixel;
				cout << "r:" << r << " g:" << g << " b:" << b << endl;
				cout << "highest found! " << i << " " << j << endl;
				waitKey(0);
			}
			//else cout << "no" << endl;
		}
	}
	cout << "Looking for lowest" << endl;
	cout << "rows "; cout << skeleton.rows-1 << endl;
	cout << "cols "; cout << skeleton.cols-1 << endl;
	waitKey(0);
	
	/*find lowest point*/
	for (int i = skeleton.rows-1; i >= 0 && !lowestFound; i--)
	{
		for (int j = skeleton.cols/3-1; j >= 0 && !lowestFound; j--)
		{
			Vec3b pixel = skeleton.at<Vec3b>(i, j);
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
				cout << "r:" << r << " g:" << g << " b:" << b << endl;
				cout << "lowest found! " << i << " " << j << endl;
				waitKey(0);
			}
		}
	}

	//imshow("COLOR", skeleton);
	//waitKey(0);
	double x = lowx - highx;
	double y = lowy - highy;

	distance = pow(x, 2) + pow(y, 2);           //calculating distance by euclidean formula
	distance = sqrt(distance);

	height = distance / 9; //convert to cm
	
	cout << "height " << height << endl;

    return height;
}