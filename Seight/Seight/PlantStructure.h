//
//  PlantStructure.h
//  Seight
//
//  Created by Paulette Constantino on 11/26/14.
//  Copyright (c) 2014 Seight Team. All rights reserved.
//

#ifndef PlantStructure_H
#define PlantStructure_H

#include <stdio.h>
#include "IPlantStructure.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace cv;

class PlantStructure : public IPlantStructure
{
public:
    PlantStructure();
    ~PlantStructure();
    Vector<Point> perform(Mat skeleton);
};

#endif /* defined(defaultEdgeDetect_H) */
