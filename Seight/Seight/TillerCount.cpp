//
//  TillerCount.cpp
//  Seight
//
//  Created by Paulette Constantino on 11/27/14.
//  Copyright (c) 2014 Seight Team. All rights reserved.
//

#include "stdafx.h"
#include "TillerCount.h"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

TillerCount::TillerCount()
{
}


TillerCount::~TillerCount()
{
}

bool trace(int x, int y, unsigned char *input, Mat image){
    int pixelCount = 0;
    int b, g, r;
	bool isTiller = false;
    
    do {
        b = input[image.step * x + y];
        g = input[image.step * x + y +1];
        r = input[image.step * x + y + 2];
    } while (b == 0 && g == 0 && r == 0);
    
    return isTiller;
    
    //isTiller true if at least 30 pixels
}

int countTillers(Mat image){
    int x,y,b,g,r, tiller=0;
    
    x = 0;
    y = image.rows;
    
    unsigned char *input = (unsigned char*)(image.data);
    
    do {
        b = input[image.step * x + y];
        g = input[image.step * x + y +1];
        r = input[image.step * x + y + 2];
        
        if(b == 0 && g == 0 && r == 0){
            if(trace(x, y, input, image)){
                tiller++;
            }
        }
    } while (x<image.cols && y>=0);

	return tiller;
}


int TillerCount::perform(Mat image) //vector<int>
{
    cout << "Tiller counting" << endl;
    
    int tillerCount = countTillers(image);
    
    return tillerCount;
}


