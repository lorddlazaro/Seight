#include "stdafx.h"
#include "PlantModeler.h"
#include <iostream>

using namespace std;

void PlantModeler::processImage(Mat image) //PhenotypicData
{
    cout << "processing image" << endl;
    PlantModeler::correction->perform();
    Mat segmentedImage = PlantModeler::segmentation->perform(image);
    PlantModeler::imageFiltering->perform(image);
    Mat sobel = PlantModeler::edgeDetection->perform(segmentedImage);
    Mat skeleton = PlantModeler::skeletonization->perform(segmentedImage);
    PlantModeler::structure->perform(sobel, skeleton);
    PlantModeler::countTiller();
    PlantModeler::measureHeight();
    cout << "done processing" << endl;
}

PlantModeler::PlantModeler()
{
    cout << "PlantModeler constructed... " << endl;
}

PlantModeler::~PlantModeler()
{
    
}

int PlantModeler::countTiller()
{
    return 0;
}

double PlantModeler::measureHeight()
{
    return 0.0;
}