//
//  IPlantStructure.cpp
//  Seight
//
//  Created by Paulette Constantino on 11/24/14.
//  Copyright (c) 2014 Seight Team. All rights reserved.
//

//#include "stdafx.h"
#include "IPlantStructure.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

IPlantStructure::IPlantStructure()
{
}


IPlantStructure::~IPlantStructure()
{
}

Mat IPlantStructure::perform(Mat sk, Mat ed)
{
    double alpha = 0.5;
    double beta;
    Mat es;
    
    beta = 1.0-alpha;
    addWeighted(ed, alpha, sk, beta, 0.0, es);
    
    imshow("Edge plus Skeleton", es);
    imwrite("/Users/pauletteconstantino/THESIS/COMBINED.jpg", es);
    
    return es;
}
