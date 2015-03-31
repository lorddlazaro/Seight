#include "stdafx.h"
#include "PlantModeler.h"
#include "HeightMeasurer.h"
#include "PlantPhenotyper.h"
#include "PixelConverter.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace cv;

void PlantModeler::processImage(Mat image, string filename) //PhenotypicData
{
    ofstream myfile;

	//HeightMeasurer* heightMeasurer = new HeightMeasurer;


	//PERFORM PREPROCESSING
	//Mat correctedImage = PlantModeler::correction->perform(image);
	Mat preprocessedImage = PlantModeler::preprocess->perform(image);
	Mat segmentedImage = PlantModeler::segmentation->perform(preprocessedImage);
    //Mat filteredImage = PlantModeler::imageFiltering->perform(segmentedImage);
    Mat edge = PlantModeler::edgeDetection->perform(segmentedImage);
    Mat skeleton = PlantModeler::skeletonization->perform(segmentedImage);
    
	//GET TILLER COUNT AND SAVE
    int tiller = PlantModeler::tillerCount->perform(edge, segmentedImage);
	myfile.open(PlantPhenotyper::getExeDir().append("/Seight/data/tillerResults.csv"), ios_base::app);
    myfile << filename + "," << tiller << "\n";
    myfile.close();
    
	//GET HEIGHT AND SAVE
    PixelConverter* pixelConverter = new PixelConverter;
    double length = PlantModeler::heightMeasure->perform(skeleton);
    Mat markedSkeleton = PlantModeler::heightMeasure->getMarkedImage();
    string markedSkeletonDirectory = PlantPhenotyper::getExeDir().append("/Seight/data/markedSkeleton/");
    string imageFile = "";
    imageFile.append(markedSkeletonDirectory);
    imageFile.append(filename);
    cout << imageFile << endl;
    imwrite(imageFile, markedSkeleton);
    double manualLength = -1;
    string traced = PlantPhenotyper::getExeDir().append("/Seight/data/trace/").append(filename);
    Mat manuallyTacedTiller = imread(traced);
    if(!manuallyTacedTiller.data)
    {
        cout << "manually traced data " << traced << " not found" << endl;
    }
    else
    {
        cvtColor(manuallyTacedTiller, manuallyTacedTiller, CV_BGR2GRAY);
        manualLength = PlantModeler::heightMeasure->perform(manuallyTacedTiller);
    }
    cout << "Manual Length : System Length \t\t" << manualLength << " : " << length << endl;
    Mat dupe;
    image.copyTo(dupe);
    double height = pixelConverter->convertImagePixelstoCentimeter(image, length);
    double manualHeight = pixelConverter->convertImagePixelstoCentimeter(dupe, manualLength);
    cout << "Manual Height : System Height \t\t" << manualHeight << " : " << height << endl;
	myfile.open(PlantPhenotyper::getExeDir().append("/Seight/data/heightResults.csv"), ios_base::app);
	myfile << filename + "," << manualLength << "," << manualHeight << "," << length << "," << height << "\n";
    myfile.close();

	//SAVE PREPROCESSING IMAGES
	cout << "Saving Preprocessed images..." << endl;
	string hsvDirectory = PlantPhenotyper::getExeDir().append("/Seight/data/HSV-Results/");
    imageFile = "";
    imageFile.append(hsvDirectory);
    imageFile.append(filename);
    cout << imageFile << endl;
    imwrite(imageFile, segmentedImage);


	string histDirectory = PlantPhenotyper::getExeDir().append("/Seight/data/EqHist/");
	imageFile.append(histDirectory);
	imageFile.append(filename);
	cout << imageFile << endl;
	imwrite(imageFile, preprocessedImage);

	string edgeDirectory = PlantPhenotyper::getExeDir().append("/Seight/data/Edge-Results/");
    imageFile = "";
    imageFile.append(edgeDirectory);
    imageFile.append(filename);
    cout << imageFile << endl;
    imwrite(imageFile, edge);

	string skeletonDirectory = PlantPhenotyper::getExeDir().append("/Seight/data/Skeleton-Results/");
    imageFile = "";
    imageFile.append(skeletonDirectory);
    imageFile.append(filename);
    cout << imageFile << endl;
    bitwise_not(skeleton, skeleton);
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
    //double pixelsIncm = 9;
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
   // waitKey(0);
    //cout << "rows "; cout << skeleton.rows << endl;
    //cout << "cols "; cout << skeleton.cols << endl;
    
    //cout << "Looking for highest" << endl;
    //waitKey(0);
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
                //waitKey(0);
            }
            //else cout << "no" << endl;
        }
    }
    //cout << "Looking for lowest" << endl;
    //cout << "rows "; cout << skeleton.rows-1 << endl;
    //cout << "cols "; cout << skeleton.cols-1 << endl;
    //waitKey(0);
	
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
                //waitKey(0);
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