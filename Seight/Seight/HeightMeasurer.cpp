//#include "stdafx.h"
#include "HeightMeasurer.h"


HeightMeasurer::HeightMeasurer()
{
}


HeightMeasurer::~HeightMeasurer()
{
}

float HeightMeasurer::perform(Mat image)
{
    int height = measureHeight(image);
    return height;
}

Mat skeleton;

Mat HeightMeasurer::getMarkedImage()
{
    return skeleton;
}

int HeightMeasurer::measureHeight(Mat image)
{
	cvtColor(image, skeleton, CV_GRAY2BGR);
	vector<Point> tiller;
	tiller.clear();
	
	//getTopPixel
	Point topPixel = getTopPixel();
	cout << topPixel.y << ", " << topPixel.x << endl;
	markPixel(topPixel);

	Point currentPixel = topPixel;
	tiller.push_back(currentPixel);
	cout << "Identifying tillers..." << endl;
	do
	{
		currentPixel = getNextPixel(currentPixel, tiller);
		tiller.push_back(currentPixel);
		markPixel(currentPixel);
		
	} while (!(currentPixel.x == 0 && currentPixel.y == 0) && currentPixel.x != image.rows - 1);
	cout << "Done!" << endl;
	//imwrite("E:/THESIS -Butil/Seightv2/Seightv2/images/heightImage/0.PNG", skeleton);
    
    double heightPixel = 0.0;
    /*** GETTING HEIGHT BY PIXEL COUNTING ONLY ***/
    //heightPixel = (int)tiller.size();
    
    
    /*** GETTING HEIGHT BY EUCLIDEAN DISTANCE ***/
    heightPixel = computeAllEuclideanDistance(tiller);

	return heightPixel;
}

double HeightMeasurer::computeAllEuclideanDistance(vector<Point> tiller)
{
    double height = 0.0;
    
    cout << "tiller size" << tiller.size() << endl;
    
    for (int i = 0; i < tiller.size(); i++) {
        if(i+1 != tiller.size())
        {
            double distance = 0;
            int x = abs(tiller[i].x - tiller[i+1].x);
            int y = abs(tiller[i].y - tiller[i+1].y);
            distance = pow(x, 2) + pow(y, 2);
            distance = sqrt(distance);
            height += distance;
        }
    }
    cout << "Height ED: " << height << endl;
    return height;
}

Point HeightMeasurer::getTopPixel(){
	Point topPixel = Point(0,0);
	bool highestFound = false;

	for (int i = 0; i < skeleton.rows && !highestFound; i++)
	{
		for (int j = 0; j < skeleton.cols && !highestFound; j++)
		{
			Vec3b pixel = skeleton.at<Vec3b>(i, j);
			int b = pixel.val[0];
			int g = pixel.val[1];
			int r = pixel.val[2];
			if (b == 255 && g == 255 && r == 255){
				topPixel = Point(i, j);
				highestFound = true;
			}
		}
	}
	

	return topPixel;
}

Point HeightMeasurer::getNextPixel(Point currentPixel, vector<Point> previousPixels)
{
	Point nextPixel = Point(0,0);
	int x = currentPixel.x;
	int y = currentPixel.y;
	/***FOR DEBUGGING. REMOVE LATER.***
	cout << "1 ";
	int b = image.at<Vec3b>(x+1, y).val[0];
	int g = image.at<Vec3b>(x+1, y).val[1];
	int r = image.at<Vec3b>(x+1, y).val[2];
	cout << b << " + " << g << " + " << r << endl;

	cout << "2 ";
	 b = image.at<Vec3b>(x+1, y + 1).val[0];
	 g = image.at<Vec3b>(x+1, y + 1).val[1];
	 r = image.at<Vec3b>(x+1, y + 1).val[2];
	cout << b << " + " << g << " + " << r << endl;

	cout << "3 ";
	 b = image.at<Vec3b>(x+1, y - 1).val[0];
	 g = image.at<Vec3b>(x+1, y - 1).val[1];
	 r = image.at<Vec3b>(x, y + 1).val[2];
	cout << b << " + " << g << " + " << r << endl;

	cout << "x, y+1 == ";
	 b = image.at<Vec3b>(x, y + 1).val[0];
	 g = image.at<Vec3b>(x, y + 1).val[1];
	 r = image.at<Vec3b>(x, y + 1).val[2];
	cout << b << " + " << g << " + " << r << endl;

	cout << "x, y-1 == ";
	 b = image.at<Vec3b>(x, y - 1).val[0];
	 g = image.at<Vec3b>(x, y - 1).val[1];
	 r = image.at<Vec3b>(x, y - 1).val[2];
	cout << b << " + " << g << " + " << r << endl;
	******/

	if (
		(x + 1) != skeleton.rows &&
		skeleton.at<Vec3b>(x + 1, y).val[0] == 255 &&
		skeleton.at<Vec3b>(x + 1, y).val[1] == 255 &&
		skeleton.at<Vec3b>(x + 1, y).val[2] == 255)
	{
		// cout << " 1 " << endl;
		nextPixel.x = x + 1;
		nextPixel.y = y;
	}
	else if (
		(x + 1) != skeleton.rows &&
		(y + 1) != skeleton.cols &&
		skeleton.at<Vec3b>(x + 1, y+1).val[0] == 255 &&
		skeleton.at<Vec3b>(x + 1, y+1).val[1] == 255 &&
		skeleton.at<Vec3b>(x + 1, y+1).val[2] == 255)
	{
		//cout << " 2 " << endl;
		nextPixel.x = x + 1;
		nextPixel.y = y + 1;
	}
	else if (
		(x + 1) != skeleton.rows &&
		(y - 1) >= 0 &&
		skeleton.at<Vec3b>(x + 1, y - 1).val[0] == 255 &&
		skeleton.at<Vec3b>(x + 1, y - 1).val[1] == 255 &&
		skeleton.at<Vec3b>(x + 1, y - 1).val[2] == 255)
	{
		//cout << " 3 " << endl;
		nextPixel.x = x + 1;
		nextPixel.y = y - 1;
	}
	else if (
		(y + 1) != skeleton.cols &&
		skeleton.at<Vec3b>(x, y + 1).val[0] == 255 &&
		skeleton.at<Vec3b>(x, y + 1).val[1] == 255 &&
		skeleton.at<Vec3b>(x, y + 1).val[2] == 255)
	{
		//cout << " 4 " << endl;
		nextPixel.x = x;
		nextPixel.y = y + 1;
	}
	else if (
		(y - 1) >= 0 &&
		skeleton.at<Vec3b>(x, y - 1).val[0] == 255 &&
		skeleton.at<Vec3b>(x, y - 1).val[1] == 255 &&
		skeleton.at<Vec3b>(x, y - 1).val[2] == 255)
	{
		//cout << " 5 " << endl;
		nextPixel.x = x;
		nextPixel.y = y - 1;
	}

	return nextPixel;
}

void HeightMeasurer::markPixel(Point point)
{
	skeleton.at<Vec3b>(point.x, point.y).val[0] = 0;
	skeleton.at<Vec3b>(point.x, point.y).val[1] = 0;
	skeleton.at<Vec3b>(point.x, point.y).val[2] = 255;
}