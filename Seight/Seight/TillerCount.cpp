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

bool TillerCount::checkHSV(Mat seg_roi, int x, int y){
    bool isBlack;
    int b, g, r;
    
    
    Vec3b pixel_s = seg_roi.at<Vec3b>(y,x);
    b = pixel_s[0];
    g = pixel_s[1];
    r = pixel_s[2];
    
    if(b==0 && g==0 && r==0){
        isBlack = true;
    }
    else isBlack = false;
    
    return isBlack;
}

int TillerCount::countTillers(Mat edge, Mat segmented){
    Rect rectROI = Rect(160, 515, 106, 106);
    Mat edge_roi = edge(rectROI);
    Mat seg_roi = segmented(rectROI);
    
    imwrite("/Users/pauletteconstantino/THESIS/ROI.JPG", seg_roi);
    
    int tiller=0;
    int b, g, r;
    //unsigned char *input = (unsigned char*)(image.data);
    
    int y = edge_roi.rows/2;
    for (int x = 0; x<edge_roi.cols; x++) {
    
        Vec3b pixel_e = edge_roi.at<Vec3b>(y,x);
        
        b = pixel_e[0];
        g = pixel_e[1];
        r = pixel_e[2];
        
        //cout << "r:" << r << " g:" << g << " b:" << b << endl;
        
        if(b>0 && g>0 && r>0){
            if(x+1<seg_roi.cols){
                if(checkHSV(seg_roi, x+1, y)==false){
                    tiller++;
                }
            }
        }
    }
    
    printf("Tiller count is: %d\n", tiller);

	return tiller;
}


int TillerCount::perform(Mat edge, Mat segmented) //vector<int>
{
    cout << "Tiller counting" << endl;
    
    int tillerCount=countTillers(edge, segmented);
    
    return tillerCount;
}


