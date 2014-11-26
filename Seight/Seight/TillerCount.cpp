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

void checkSurrounding(int x, int y){

}

int TillerCount::perform(Mat image) //vector<int>
{
    cout << "Tiller counting" << endl;
    
    int x,y,b,g,r;
    
    unsigned char *input = (unsigned char*)(image.data);
    
    for (x=0; x<image.cols; x++) {
        for (y=image.rows; y>=0; y--) {
            b = input[image.step * x + y];
            g = input[image.step * x + y +1];
            r = input[image.step * x + y + 2];
            
            if(b == 0 && g == 0 && r == 0){
                checkSurrounding(x, y);
                
            }
        }
    }
    
    return tillerCount;
}


