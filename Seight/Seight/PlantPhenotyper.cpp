#include "stdafx.h"
#include "PlantPhenotyper.h"
#include "PlantModeler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <windows.h>
#include <string>

using namespace cv;
using namespace std;

PlantPhenotyper::PlantPhenotyper()
{
	cout << "creating approach in plant phenotyper constructor" << endl;
	PlantPhenotyper::plantModeler = PlantModeler::createApproach(PlantModeler::APPROACH_A);
}

PlantPhenotyper::~PlantPhenotyper()
{
}

int PlantPhenotyper::phenotype()
{
	Mat image;
	string directory = getExeDir();
	directory.append("\\Seight\\data\\");
	string datasetDirectory = "data_gathering_3\\";
	directory.append(datasetDirectory);
	string imageNameConvention = "IR64-";
	string fileExtension = ".JPG";
	string filename = "";
	string imageFilename = "";
	/*loop images to phenotype*/
	for (int i = 1; i <= 60; i++)
	{
		//SET FILE NAME
		filename = "";
		filename.append(imageNameConvention);
		if (i < 10)
		{
			filename.append("00");  //IR64-00i
		}
		else if (10 <= i && i < 100)
		{
			filename.append("0"); //IR64-0i
		}
		filename.append(to_string(i));
		filename.append(fileExtension);
		//SET FULL FILENAME AND DIRECTORY
		imageFilename = "";
		imageFilename.append(directory);
		imageFilename.append(filename);
		//READ IMAGE AND START PHENOTYPING
		image = imread(imageFilename, CV_LOAD_IMAGE_COLOR);   // Read the file
		if (!image.data)                           // Check for invalid input
		{
			cout << "Could not open or find the image: " << imageFilename << std::endl;
		}
		else
		{
			cout << "Opened " << imageFilename << endl;
			PlantPhenotyper::plantModeler.processImage(image, filename);
		}
	}

	return 1;
}

string PlantPhenotyper::getExeDir()
{
	//Get Exe File Name
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);

	//Get Exe Path
	std::string f = std::string(buffer);
	string directory = f.substr(0, f.find_last_of("\\/"));

	//go out of debug folder
	//cout << directory << endl;
	directory.resize(directory.size() - 6); //"\debug" is 6 characters
	return directory;
}