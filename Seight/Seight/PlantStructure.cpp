//
//  PlantStructure.cpp
//  Seight
//
//  Created by Paulette Constantino on 11/26/14.
//  Copyright (c) 2014 Seight Team. All rights reserved.
//
#include "stdafx.h"
#include "PlantStructure.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>


using namespace cv;
using namespace std;

PlantStructure::PlantStructure()
{
}

PlantStructure::~PlantStructure()
{
}

Vector<Point> trace(Mat image){
    int b, g, r;
    Vector<Point> img_points;
    unsigned char *input = (unsigned char*)(image.data);
    
    for (int y = image.rows-1; y>=0; y--) {
        for (int x = 0; x<image.cols; x++) {
            b = input[image.step * x + y];
            g = input[image.step * x + y +1];
            r = input[image.step * x + y + 2];
            
            if(b==0 && g==0 && r==0){
                img_points.push_back(Point(x,y));
            }
        }
    }
    
    return img_points;
}

Vector<Point> PlantStructure::perform(Mat skeleton)
{
    cout << "performing Plant Structure" << endl;
    
    Vector<Point> img_points;
    
    img_points = trace(skeleton);
    
    
    /*double alpha = 0.5;
    double beta;
    
    beta = 1.0-alpha;*/
    
    
    //addWeighted(edge, alpha, skeleton, beta, 0.0, structure);
    
    //imshow("Edge plus Skeleton", structure);
    //waitKey(0);
    //imwrite("/Users/pauletteconstantino/THESIS/structure2.JPG", structure);
    
    return img_points;
}

