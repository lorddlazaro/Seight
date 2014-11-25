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
    Mat ps = PlantModeler::structure->perform(sobel, skeleton);
    PlantModeler::countTiller(ps);
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

int PlantModeler::countTiller(Mat image)
{
    int x,y,b,g,r;
    
    unsigned char *input = (unsigned char*)(image.data);
    
    for (y=image.rows; y>=0; y--) {
        for (x=0; x<image.cols; x++) {
            b = input[image.step * x + y];
            g = input[image.step * x + y +1];
            r = input[image.step * x + y + 2];
            
            if(b == 255 && g == 255 && r == 255){
                printf("Black\n");
                printf("X is %d Y is %d\n", x, y);
                
            }
        }
    }
    
    return 0;
}

double PlantModeler::measureHeight()
{
    return 0.0;
}