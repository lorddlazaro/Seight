//
//  IPlantStructure.h
//  Seight
//
//  Created by Paulette Constantino on 11/24/14.
//  Copyright (c) 2014 Seight Team. All rights reserved.
//

#ifndef IPlantStructure_H
#define IPlantStructure_H

#include <stdio.h>
#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace cv;

class IPlantStructure
{
public:
    IPlantStructure();
    ~IPlantStructure();
    virtual Vector<Point> perform(Mat sk);
};


#endif /* defined(IPlantStructure_H) */
