#include "stdafx.h"
#include "PlantModeler.h"
#include <iostream>

using namespace std;

void PlantModeler::processImage(Mat image) //PhenotypicData
{
    cout << "processing image" << endl;
    PlantModeler::correction->perform();
    Mat segmentedImage = PlantModeler::segmentation->perform(image);
    PlantModeler::imageFiltering->perform(segmentedImage);
    Mat edge = PlantModeler::edgeDetection->perform(segmentedImage);
    Mat skeleton = PlantModeler::skeletonization->perform(segmentedImage);
    Vector<Point> img_points = PlantModeler::structure->perform(skeleton);
    PlantModeler::tillerCount->perform(edge);
    PlantModeler::measureHeight();
    cout << "done processing" << endl;
}

PlantModeler::PlantModeler()
{
    cout << "PlantModeler constructed... " << endl;
}

PlantModeler::~PlantModeler(){
    
}

/*void traceUp(int x, int y, unsigned char *input, Mat image){
    int pixelCount = 0;
    int b, g, r;
    
    do {
        b = input[image.step * x + y];
        g = input[image.step * x + y +1];
        r = input[image.step * x + y + 2];
    } while (b == 0 && g == 0 && r == 0);
}

int TillerCount::perform(Mat image) //vector<int>
{
    cout << "Tiller counting" << endl;
    
    int x,y,b,g,r, tillerCount=0;
    x = 0;
    y = image.rows;
    
    unsigned char *input = (unsigned char*)(image.data);
    
    do {
        b = input[image.step * x + y];
        g = input[image.step * x + y +1];
        r = input[image.step * x + y + 2];
        
        if(b == 0 && g == 0 && r == 0){
            traceUp(x, y, input, image);
        }
    } while (x<image.cols && y>=0);
    
    return tillerCount;
}*/

double PlantModeler::measureHeight()
{
    return 0.0;
}