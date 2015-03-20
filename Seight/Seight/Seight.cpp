// Seight.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Plant.h"
#include "PlantDAO.h"
#include "SQLPlantDAO.h"
#include "PlantPhenotyper.h"
#include <windows.h>

using namespace std;

int main()
{
	//BASIC OPENCV TESTING: opening and outputing images
	//cv::Mat image;
	//cout << "Size: " << image.size().height << ", " << image.size().width << std::endl;
	//
	//string directory = PlantPhenotyper::getExeDir();
	//directory.append("\\Seight\\data\\");
	//string filename = "test.jpg";
	//image = imread( directory + filename);


	//if (!image.data){
	//	cout << "Image not loaded" << endl;
	//}
	//else{
	//	cout << "Image loaded" << endl;
	//}

	//cv::namedWindow("Test Image");
	//cv::imshow("Test Image", image);
	//cv::waitKey(0);
	
	PlantPhenotyper* plantPhenotyper = new PlantPhenotyper;
	plantPhenotyper->phenotype();
	
	cin.ignore();

	return 0;
}
