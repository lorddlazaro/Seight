// Seight.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Plant.h"
#include "PlantDAO.h"
#include "SQLPlantDAO.h"
#include "PlantPhenotyper.h"

using namespace std;

int main()
{

	/*
	 * HSV Segment Slider
	 *
	 *
	// Read original image 
	Mat src = imread("D:/DE LA SALLE UNIVERSITY/Work/Programming/Seight/Seight/Seight/image/EqHist/IR64-003.jpg");

	//if fail to read the image
	if (!src.data)
	{
		cout << "Error loading the image" << endl;
		return -1;
	}

	// Create a window
	namedWindow("My Window", 1);

	//Create trackbar to change brightness
	int iSliderValue1a = 0;
	int iSliderValue1b = 0;
	int iSliderValue1c = 0;
	createTrackbar("H1", "My Window", &iSliderValue1a, 255);
	createTrackbar("S1", "My Window", &iSliderValue1b, 255);
	createTrackbar("V1", "My Window", &iSliderValue1c, 255);

	//Create trackbar to change contrast
	int iSliderValue2a = 255;
	int iSliderValue2b = 255;
	int iSliderValue2c = 255;
	createTrackbar("H2", "My Window", &iSliderValue2a, 255);
	createTrackbar("S2", "My Window", &iSliderValue2b, 255);
	createTrackbar("V2", "My Window", &iSliderValue2c, 255);

	while (true)
	{
		Mat hsvImage;
		//Convert image to HSV
		cvtColor(src, hsvImage, CV_BGR2HSV);

		//hsv1=30,50,50 | 115,255,50
		//hsv2=30,70,70 | 80,250,255
		//hsv3=

		//imshow("MyWindow", hsvImage);

		//define range of green color in HSV
		Scalar green_min = Scalar(iSliderValue1a, iSliderValue1b, iSliderValue1c);//30, 50, 50 (70, 100, 30);
		Scalar green_max = Scalar(iSliderValue2a, iSliderValue2b, iSliderValue2c);//(115, 255, 50);

		Mat mask;

		inRange(hsvImage, green_min, green_max, mask);

		//imshow("mask", mask);

		Mat result;
		src.copyTo(result, mask);

		
		//show the brightness and contrast adjusted image
		imshow("res", result);

		// Wait until user press some key for 50ms
		int iKey = waitKey(50);

		//if user press 'ESC' key
		if (iKey == 27)
		{
			break;
		}
	}/**/


	
	//PlantDAO* plantDAO = new SQLPlantDAO;
	//Plant* plant = new Plant;
	//(*plantDAO).insertPlant(*plant);


	//get new plants
	PlantPhenotyper* plantPhenotyper = new PlantPhenotyper;
	plantPhenotyper->phenotype(/*list of plants*/);
	cin.ignore();

	return 0;
}

