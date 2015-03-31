//
//  normalizeAdjustBrightnessAndContrastPreprocess.cpp
//  Seight
//
//  Created by Elisha Jeremy Gonzales on 3/30/15.
//  Copyright (c) 2015 Butil. All rights reserved.
//

#include "normalizeAdjustBrightnessAndContrastPreprocess.h"

normalizeAdjustBrightnessAndContrastPreprocess::normalizeAdjustBrightnessAndContrastPreprocess()
{
}

normalizeAdjustBrightnessAndContrastPreprocess::~normalizeAdjustBrightnessAndContrastPreprocess()
{
}

Mat normalizeAdjustBrightnessAndContrastPreprocess::perform(Mat image)
{
    Mat preprocessed;
    
    normalize(image, preprocessed, 0, 255, NORM_MINMAX, CV_8UC1);
    preprocessed = preprocessed + Scalar(5,5,5); //Adjust Brightness
    preprocessed.convertTo(preprocessed, -1, 1.7, 0); //Adjust Contrast
    
    return preprocessed;
}