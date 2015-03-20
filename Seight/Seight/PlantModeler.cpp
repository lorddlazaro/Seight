#include "stdafx.h"
#include "PlantModeler.h"
#include "PlantPhenotyper.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void PlantModeler::processImage(Mat image, string filename) //PhenotypicData
{
    ofstream myfile;

	//PERFORM PREPROCESSING
    //Mat correctedImage = PlantModeler::correction->perform(image);
    Mat segmentedImage = PlantModeler::segmentation->perform(image);
    //Mat filteredImage = PlantModeler::imageFiltering->perform(segmentedImage);
    Mat edge = PlantModeler::edgeDetection->perform(segmentedImage);
    Mat skeleton = PlantModeler::skeletonization->perform(segmentedImage);
    
	//GET TILLER COUNT AND SAVE
    int tiller = PlantModeler::tillerCount->perform(edge, segmentedImage);
	myfile.open(PlantPhenotyper::getExeDir().append("\\Seight\\data\\tillerResults.csv"), ios_base::app);
    myfile << filename + "," << tiller << "\n";
    myfile.close();

	//GET HEIGHT AND SAVE
	myfile.open(PlantPhenotyper::getExeDir().append("\\Seight\\data\\heightResults.csv"), ios_base::app);
    double height = PlantModeler::measureHeight(skeleton);
	myfile << filename + "," << height << "\n";
    myfile.close();

	//SAVE PREPROCESSING IMAGES
	cout << "Saving Preprocessed images..." << endl;
	string hsvDirectory = PlantPhenotyper::getExeDir().append("\\Seight\\data\\HSV-Results\\");
    string imageFile = "";
    imageFile.append(hsvDirectory);
    imageFile.append(filename);
    cout << imageFile << endl;
    imwrite(imageFile, segmentedImage);


	string edgeDirectory = PlantPhenotyper::getExeDir().append("\\Seight\\data\\Edge-Results\\");
    imageFile = "";
    imageFile.append(edgeDirectory);
    imageFile.append(filename);
    cout << imageFile << endl;
    imwrite(imageFile, edge);


	string skeletonDirectory = PlantPhenotyper::getExeDir().append("\\Seight\\data\\Skeleton-Results\\");
    imageFile = "";
    imageFile.append(skeletonDirectory);
    imageFile.append(filename);
    cout << imageFile << endl;
    imwrite(imageFile, skeleton);
}

PlantModeler::PlantModeler()
{
    cout << "PlantModeler constructed... " << endl;
}

PlantModeler::~PlantModeler(){
    
}

double PlantModeler::measureHeight(Mat skeleton)
{
    double pixelsIncm = 9;
    double height;
    double distance;
    int b, g, r;
    //unsigned char *input = (unsigned char*)(image.data);
    bool highestFound = false, lowestFound = false;
    int highx = 0, highy = 0, lowx = 0, lowy = 0;
    
    //cout << skeleton << endl;
    cvtColor(skeleton, skeleton, CV_GRAY2BGR);
    
    /*find highest point*/
    //imshow("SKEL", skeleton);
    waitKey(0);
    //cout << "rows "; cout << skeleton.rows << endl;
    //cout << "cols "; cout << skeleton.cols << endl;
    
    //cout << "Looking for highest" << endl;
    waitKey(0);
    for (int i = 0; i < skeleton.rows && !highestFound; i++)
    {
        for (int j = 0; j < skeleton.cols && !highestFound; j++)
        {
            //cout << skeleton.at<Vec3b>(i, j) << endl;
            Vec3b pixel = skeleton.at<Vec3b>(i, j);
            //cout << "i" << i;
            //cout << "j" << j << endl;
            //waitKey(0);
            b = pixel.val[0];
            g = pixel.val[1];
            r = pixel.val[2];
            
            //cout << "r:" << r << " g:" << g << " b:" << b << endl;
            
            if (b == 255 && g == 255 && r == 255){
                //cout << "yes" << endl;
                highx = i;
                highy = j;
                highestFound = true;
                skeleton.at<Vec3b>(i, j) = pixel;
                //cout << "r:" << r << " g:" << g << " b:" << b << endl;
                //cout << "highest found! " << i << " " << j << endl;
                waitKey(0);
            }
            //else cout << "no" << endl;
        }
    }
    //cout << "Looking for lowest" << endl;
    //cout << "rows "; cout << skeleton.rows-1 << endl;
    //cout << "cols "; cout << skeleton.cols-1 << endl;
    waitKey(0);
    
    /*find lowest point*/
    for (int i = skeleton.rows-1; i >= 0 && !lowestFound; i--)
    {
        for (int j = skeleton.cols-1; j >= 0 && !lowestFound; j--)
        {
            Vec3b pixel = skeleton.at<Vec3b>(i, j);
            //cout << "i" << i;
            //cout << "j" << j << endl;
            b = pixel[0];
            g = pixel[1];
            r = pixel[2];
            //cout << "r:" << r << " g:" << g << " b:" << b << endl;
            if (b == 255 && g == 255 && r == 255){
                lowx = i;
                lowy = j;
                lowestFound = true;
                //cout << "r:" << r << " g:" << g << " b:" << b << endl;
                //cout << "lowest found! " << i << " " << j << endl;
                waitKey(0);
            }
        }
    }
    
    //imshow("COLOR", skeleton);
    //waitKey(0);
    double x = lowx - highx;
    double y = lowy - highy;
    
    distance = pow(x, 2) + pow(y, 2);           //calculating distance by euclidean formula
    distance = sqrt(distance);
    
    height = distance / 9; //convert to cm
    
    cout << "Height: \t" << height << endl;
    
    return height;
}