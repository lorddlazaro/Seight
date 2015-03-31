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
#include <vector>
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

bool TillerCount::checkBlackPixel(Mat seg_roi, int x, int y){
	bool isBlack;
	int b, g, r;


	Vec3b pixel_s = seg_roi.at<Vec3b>(y, x);
	b = pixel_s[0];
	g = pixel_s[1];
	r = pixel_s[2];

	if (b == 0 && g == 0 && r == 0){
		isBlack = true;
	}
	else isBlack = false;

	return isBlack;
}

int TillerCount::getMode(std::vector<int> tillerData){
	int mode = 0;
	int countMode = 0, countCur = 0;
	int curNum = tillerData.at(0);

	std::sort(tillerData.begin(), tillerData.end());

	for (int i = 0; i<tillerData.size(); i++){
		if (curNum == tillerData.at(i)){
			countCur++;
		}
		else{
			if (countCur>countMode){
				mode = curNum;
				countMode = countCur;
			}
			countCur = 1;
		}
		curNum = tillerData.at(i);
	}

	return mode;
}

int TillerCount::countTillers(Mat edge, Mat segmented){
	//Rect rectROI = Rect(23, 380, 170, 75); //for new pictures
	//Rect rectROI = Rect(160, 515, 106, 106); //old ROI (for pictures with meter stick)
	
    int x_max = edge.cols;
    int y_max = edge.rows;
    int x_start = x_max/3; //3 because 1/3
    int y_start = y_max-(y_max/8); //8 because 1/8
    int width = x_max/3;
    int length = (y_max/8)-1;
    
    Rect rectROI = Rect(x_start, y_start, width, length);
    
    Mat edge_roi = edge(rectROI);
	Mat seg_roi = segmented(rectROI);

	/*imwrite("/Users/pauletteconstantino/THESIS/Seight/Seight/Seight/Seight/data/ROI_edge.JPG", edge_roi);
	imwrite("/Users/pauletteconstantino/THESIS/Seight/Seight/Seight/Seight/data/ROI_seg.JPG", seg_roi);*/

	int tillerSum = 0, tiller = 0;
	int b, g, r;
	//int x_prev = 0;
	std::vector<int> tillerData;
	//put tiller values per row in array then get mode

	for (int y = 0; y<edge_roi.rows; y++){
		for (int x = 0; x<edge_roi.cols; x++) {

			Vec3b pixel_e = edge_roi.at<Vec3b>(y, x);

			b = pixel_e[0];
			g = pixel_e[1];
			r = pixel_e[2];

			//cout << "r:" << r << " g:" << g << " b:" << b << endl;

			if (b>0 || g>0 || r>0){
				if (x + 1<seg_roi.cols){
					if (checkBlackPixel(seg_roi, x + 1, y) == false){
						//x_prev = x;
						tillerSum++;
					}
					/*else if (checkBlackPixel(seg_roi, x+1, y)==true && (x-x_prev) >= 3){ //to detect leaves
					tillerSum++;
					}*/
				}
			}
		}

		//cout << "tiller sum is: " << tillerSum << endl;
		tillerData.push_back(tillerSum);
		tillerSum = 0;
	}

	tiller = getMode(tillerData);

	printf("Tiller count is: \t%d\n", tiller);

	return tiller;
}


int TillerCount::perform(Mat edge, Mat segmented) //vector<int>
{
	//cout << "Tiller counting" << endl;

	int tillerCount = countTillers(edge, segmented);

	return tillerCount;
}


