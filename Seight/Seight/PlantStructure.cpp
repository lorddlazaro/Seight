//
//  PlantStructure.cpp
//  Seight
//
//  Created by Paulette Constantino on 11/26/14.
//  Copyright (c) 2014 Seight Team. All rights reserved.
//
#include "stdafx.h"
#include "PlantStructure.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

PlantStructure::PlantStructure()
{
}

PlantStructure::~PlantStructure()
{
}

Mat PlantStructure::perform(Mat skeleton, Mat edge)
{
    cout << "performing Plant Structure" << endl;
    
    Mat structure;
    double alpha = 0.5;
    double beta;
    
    beta = 1.0-alpha;
    addWeighted(edge, alpha, skeleton, beta, 0.0, structure);
    
    //imshow("Edge plus Skeleton", structure);
    //waitKey(0);
    //imwrite("/Users/pauletteconstantino/THESIS/structure2.JPG", structure);
    
    return structure;
}

