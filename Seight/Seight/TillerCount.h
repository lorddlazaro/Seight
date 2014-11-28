//
//  TillerCount.h
//  Seight
//
//  Created by Paulette Constantino on 11/27/14.
//  Copyright (c) 2014 Seight Team. All rights reserved.
//

#ifndef TillerCount_H
#define TillerCount_H

#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class TillerCount
{
public:
    TillerCount();
    ~TillerCount();
    int perform(Mat img); //vector<int>
    void trace(int x, int y, unsigned char *input, Mat image);
};

#endif /* defined(__Seight__TillerCount__) */
