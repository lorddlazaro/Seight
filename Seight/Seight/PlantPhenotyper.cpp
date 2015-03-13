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

std::string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}

std::string GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}

int PlantPhenotyper::phenotype()
{
	Mat image;
	//string directory = "D:/De La Salle University/Work/Programming/Seight/Seight/Seight/image/Resized/";
	string directory = GetExePath();
	directory.resize(directory.size() - 6);
	directory.append("\\Seight\\image\\Resized\\");
	cout << "my directory is " << GetExePath() << "\n";
	string imageNameConvention = "IR64-0";
	string fileExtension = ".JPG";
	string filename = "";
	string imageFilename = "";
	/*loop images to phenotype*/
	for (int i = 1; i <= 24; i++)
	{
		imageFilename = "";
		filename = "";
		imageFilename.append(directory);
		filename.append(imageNameConvention);
		if (i < 10)
		{
			filename.append("0");
			filename.append(to_string(i));
		}
		else
		{
			filename.append(to_string(i));
		}
		filename.append(fileExtension);
		imageFilename.append(filename);
		image = imread(imageFilename/*"/Users/pauletteconstantino/THESIS/Seight/Seight/Seight/IR64-009_NoRuler_Resize.JPG"*/, CV_LOAD_IMAGE_COLOR);   // Read the file
		if (!image.data)                           // Check for invalid input
		{
			cout << "Could not open or find the image: " << imageFilename << std::endl;
		}
		else
		{
			cout << "Opened " << i << endl;
			PlantPhenotyper::plantModeler.processImage(image, filename);
		}
	}

	return 1;
}