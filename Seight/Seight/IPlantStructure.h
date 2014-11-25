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
//#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class IPlantStructure
{
public:
    IPlantStructure();
    ~IPlantStructure();
    virtual Mat perform(Mat sk, Mat ed);
};


#endif /* defined(__Seight__IPlantStructure__) */
