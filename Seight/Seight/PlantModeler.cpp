#include "stdafx.h"
#include "PlantModeler.h"
#include <iostream>

using namespace std;

void PlantModeler::processImage(Mat image) //PhenotypicData
{
	cout << "processing image" << endl;
	PlantModeler::correction->perform();
	PlantModeler::segmentation->perform(image);
	PlantModeler::imageFiltering->perform();
	PlantModeler::edgeDetection->perform();
	PlantModeler::skeletonization->perform();
}

PlantModeler::PlantModeler()
{
	cout << "PlantModeler constructed... " << endl;
}

PlantModeler::~PlantModeler()
{

}
