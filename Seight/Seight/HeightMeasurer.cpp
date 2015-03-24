#include "stdafx.h"
#include "HeightMeasurer.h"


HeightMeasurer::HeightMeasurer()
{
}


HeightMeasurer::~HeightMeasurer()
{
}

int HeightMeasurer::measureHeight(Mat image)
{
	Mat skeleton;
	double cmConversion = 1; // There are 'cmConversion' pixels in 1 cm;
	int height = 0;
	cvtColor(image, skeleton, CV_GRAY2BGR);
	vector<Point> tiller;
	tiller.clear();
	
	//getTopPixel
	Point topPixel = getTopPixel(skeleton);
	cout << topPixel.y << ", " << topPixel.x << endl;
	markPixel(skeleton, topPixel);

	Point currentPixel = topPixel;
	tiller.push_back(currentPixel);
	cout << "Identifying tillers..." << endl;
	do
	{
		currentPixel = getNextPixel(skeleton, currentPixel, tiller);
		tiller.push_back(currentPixel);
		markPixel(skeleton, currentPixel);
		
	} while (!(currentPixel.x == 0 && currentPixel.y == 0) && currentPixel.x != image.rows - 1);
	cout << "Done!" << endl;
	imwrite("E:/THESIS -Butil/Seightv2/Seightv2/images/heightImage/0.PNG", skeleton);

	int heightPixel = tiller.size();
	cout << heightPixel << endl;
	height = heightPixel / cmConversion;
	return height;
}

Point HeightMeasurer::getTopPixel(Mat image){
	Point topPixel = Point(0,0);
	bool highestFound = false;

	for (int i = 0; i < image.rows && !highestFound; i++)
	{
		for (int j = 0; j < image.cols && !highestFound; j++)
		{
			Vec3b pixel = image.at<Vec3b>(i, j);
			int b = pixel.val[0];
			int g = pixel.val[1];
			int r = pixel.val[2];
			if (b == 255 && g == 255 && r == 255){
				int highx = i;
				int highy = j;
				topPixel = Point(i, j);
				highestFound = true;
			}
		}
	}
	

	return topPixel;
}

Point HeightMeasurer::getNextPixel(Mat image, Point currentPixel, vector<Point> previousPixels)
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
	/******/

	if (
		(x + 1) != image.rows &&
		image.at<Vec3b>(x + 1, y).val[0] == 255 &&
		image.at<Vec3b>(x + 1, y).val[1] == 255 &&
		image.at<Vec3b>(x + 1, y).val[2] == 255)
	{
		// cout << " 1 " << endl;
		nextPixel.x = x + 1;
		nextPixel.y = y;
	}
	else if (
		(x + 1) != image.rows &&
		(y + 1) != image.cols &&
		image.at<Vec3b>(x + 1, y+1).val[0] == 255 &&
		image.at<Vec3b>(x + 1, y+1).val[1] == 255 &&
		image.at<Vec3b>(x + 1, y+1).val[2] == 255)
	{
		//cout << " 2 " << endl;
		nextPixel.x = x + 1;
		nextPixel.y = y + 1;
	}
	else if (
		(x + 1) != image.rows &&
		(y - 1) >= 0 &&
		image.at<Vec3b>(x + 1, y - 1).val[0] == 255 &&
		image.at<Vec3b>(x + 1, y - 1).val[1] == 255 &&
		image.at<Vec3b>(x + 1, y - 1).val[2] == 255)
	{
		//cout << " 3 " << endl;
		nextPixel.x = x + 1;
		nextPixel.y = y - 1;
	}
	else if (
		(y + 1) != image.cols &&
		image.at<Vec3b>(x, y + 1).val[0] == 255 &&
		image.at<Vec3b>(x, y + 1).val[1] == 255 &&
		image.at<Vec3b>(x, y + 1).val[2] == 255)
	{
		//cout << " 4 " << endl;
		nextPixel.x = x;
		nextPixel.y = y + 1;
	}
	else if (
		(y - 1) >= 0 &&
		image.at<Vec3b>(x, y - 1).val[0] == 255 &&
		image.at<Vec3b>(x, y - 1).val[1] == 255 &&
		image.at<Vec3b>(x, y - 1).val[2] == 255)
	{
		//cout << " 5 " << endl;
		nextPixel.x = x;
		nextPixel.y = y - 1;
	}

	return nextPixel;
}

void HeightMeasurer::markPixel(Mat image, Point point)
{
	image.at<Vec3b>(point.x, point.y).val[0] = 0;
	image.at<Vec3b>(point.x, point.y).val[1] = 0;
	image.at<Vec3b>(point.x, point.y).val[2] = 255;
}