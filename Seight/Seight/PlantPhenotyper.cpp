<<<<<<< HEAD
#include "stdafx.h"
=======
////#include "stdafx.h"
>>>>>>> origin/master
#include "PlantPhenotyper.h"
#include "PlantModeler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <windows.h>
#include <string>

#include <unistd.h>

using namespace cv;
using namespace std;

PlantPhenotyper::PlantPhenotyper()
{
	cout << "creating approach in plant phenotyper constructor" << endl;
	PlantPhenotyper::plantModeler = PlantModeler::createApproach(PlantModeler::APPROACH_C);
}

PlantPhenotyper::~PlantPhenotyper()
{
}

int PlantPhenotyper::phenotype()
{
	Mat image;
	string directory = getExeDir();
	directory.append("/Seight/data/");
	string datasetDirectory = "current/";
	directory.append(datasetDirectory);
	string imageNameConvention = "";
	string fileExtension = ".PNG";
	string filename = "";
	string imageFilename = "";
    /*loop images to phenotype*/
	for (int i = 1; i <= 30; i++)
	{
		//SET FILE NAME
		filename = "";
		filename.append(imageNameConvention);
		//if (i < 10)
		//{
		//	filename.append("00");  //IR64-00i
		//}
		//else if (10 <= i && i < 100)
		//{
		//	filename.append("0"); //IR64-0i
		//}
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
			//cout << "---" << endl << "Opened " << imageFilename << endl;
			cout << "---" << endl << "Opened: \t" << filename << endl;
			PlantPhenotyper::plantModeler.processImage(image, filename);
		}
	}

	return 1;
}

string PlantPhenotyper::getExeDir()
{
	//Get Exe File Name
	/* WINDOWS */
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);

	//Get Exe Path
	std::string f = std::string(buffer);
	string directory = f.substr(0, f.find_last_of("\\/"));
    
     directory.resize(directory.size() - 6); //"\debug" is 6 characters
    /**/
    
    /* MAC */
    //string directory = "/Users/elishajeremygonzales/Documents/Seight/Seight";
    //string directory = "/Users/pauletteconstantino/THESIS/Seight/Seight/Seight";
    /**/

    
    //go out of debug folder
    //cout << directory << endl;
    
    return directory;
}