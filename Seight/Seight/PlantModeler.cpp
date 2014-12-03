#include "stdafx.h"
#include "PlantModeler.h"
#include <iostream>

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
    PlantModeler::tillerCount->perform(edge);
    PlantModeler::measureHeight(skeleton);
    cout << "done processing" << endl;
}

PlantModeler::PlantModeler()
{
    cout << "PlantModeler constructed... " << endl;
}

PlantModeler::~PlantModeler(){
    
}

/*void traceUp(int x, int y, unsigned char *input, Mat image){
    int pixelCount = 0;
    int b, g, r;
    
    do {
        b = input[image.step * x + y];
        g = input[image.step * x + y +1];
        r = input[image.step * x + y + 2];
    } while (b == 0 && g == 0 && r == 0);
}

int TillerCount::perform(Mat image) //vector<int>
{
    cout << "Tiller counting" << endl;
    
    int x,y,b,g,r, tillerCount=0;
    x = 0;
    y = image.rows;
    
    unsigned char *input = (unsigned char*)(image.data);
    
    do {
        b = input[image.step * x + y];
        g = input[image.step * x + y +1];
        r = input[image.step * x + y + 2];
        
        if(b == 0 && g == 0 && r == 0){
            traceUp(x, y, input, image);
        }
    } while (x<image.cols && y>=0);
    
    return tillerCount;
}*/

double PlantModeler::measureHeight(Mat skeleton)
{
	double pixelsIncm = 9;
	double height;
	double distance;
	int b, g, r;
	//unsigned char *input = (unsigned char*)(image.data);
	bool highestFound = false, lowestFound = false;
	int highx = 0, highy = 0, lowx = 0, lowy = 0;
	
	/*find highest point*/
	imshow("SKEL", skeleton);
	
	cout << "rows "; cout << skeleton.rows << endl;
	cout << "cols "; cout << skeleton.cols << endl;
	
	for (int i = 0; i < skeleton.rows && !highestFound; i++)
	{
		for (int j = 0; j < skeleton.cols && !highestFound; j++)
		{
			Vec3b pixel = skeleton.at<Vec3b>(i, j);
			cout << "i" << i;
			cout << "j" << j << endl;
			//waitKey(0);
			b = pixel[0];
			g = pixel[1];
			r = pixel[2];

			if (b == 255 && g == 255 && r == 255){
				highx = i;
				highy = j;
				highestFound = true;
			}
		}
	}
	
	/*find lowest point*/
	for (int i = skeleton.rows-1; i == 0 && !lowestFound; i--)
	{
		for (int j = skeleton.cols-1; j == 0 && !lowestFound; j--)
		{
			Vec3b pixel = skeleton.at<Vec3b>(i, j);
			b = pixel[0];
			g = pixel[1];
			r = pixel[2];

			if (b == 255 && g == 255 && r == 255){
				lowx = i;
				lowy = j;
				lowestFound = true;
			}
		}
	}

	double x = lowx - highx;
	double y = lowy - highy;

	distance = pow(x, 2) + pow(y, 2);           //calculating distance by euclidean formula
	distance = sqrt(distance);

	height = distance / 9; //convert to cm
	
    return height;
}