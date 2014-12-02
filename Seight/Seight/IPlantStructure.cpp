//
//  IPlantStructure.cpp
//  Seight
//
//  Created by Paulette Constantino on 11/24/14.
//  Copyright (c) 2014 Seight Team. All rights reserved.
//

#include "stdafx.h"
#include "IPlantStructure.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace cv;

IPlantStructure::IPlantStructure()
{
}


IPlantStructure::~IPlantStructure()
{
}

Vector<Point> IPlantStructure::perform(Mat sk)
{
    Vector<Point> structure_points;
    
    return structure_points;
}
