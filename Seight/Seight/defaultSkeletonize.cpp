#include "stdafx.h"
#include "defaultSkeletonize.h"
#include <iostream>

using namespace std;

defaultSkeletonize::defaultSkeletonize()
{
}


defaultSkeletonize::~defaultSkeletonize()
{
}

Mat defaultSkeletonize::perform(Mat image)
{
    //cout << "perform skeletonization" << endl;
    
    Mat bw;
    cvtColor(image, bw, CV_BGR2GRAY);
    threshold(bw, bw, 1, 255, CV_THRESH_BINARY);
    
    thinning(bw);
    //bitwise_not(bw, bw);
    
    //imshow("Thinning", bw);
    //waitKey(0);
    
    //imwrite("D:/DE LA SALLE UNIVERSITY/Work/Programming/Seight/Seight/Seight/image/result_ZhangSuen.JPG", bw, vector < int > {0});
    //imwrite("/Users/pauletteconstantino/THESIS/structure3.JPG", bw);
    
    return bw;
}

void defaultSkeletonize::thinningIteration(Mat& im, int iter)
{
    Mat marker = Mat::zeros(im.size(), CV_8UC1);
    
    for (int i = 1; i < im.rows-1; i++)
    {
        for (int j = 1; j < im.cols-1; j++)
        {
            uchar p2 = im.at<uchar>(i-1, j);
            uchar p3 = im.at<uchar>(i-1, j+1);
            uchar p4 = im.at<uchar>(i, j+1);
            uchar p5 = im.at<uchar>(i+1, j+1);
            uchar p6 = im.at<uchar>(i+1, j);
            uchar p7 = im.at<uchar>(i+1, j-1);
            uchar p8 = im.at<uchar>(i, j-1);
            uchar p9 = im.at<uchar>(i-1, j-1);
            
            int A  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
            (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
            (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
            (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
            int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
            int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
            int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);
            
            if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
                marker.at<uchar>(i,j) = 1;
        }
    }
    
    im &= ~marker;
}

void defaultSkeletonize::thinning(Mat& im)
{
    im /= 255;
    
    cv::Mat prev = cv::Mat::zeros(im.size(), CV_8UC1);
    cv::Mat diff;
    
    do {
        //cout << "in thinning ";
        thinningIteration(im, 0);
        thinningIteration(im, 1);
        cv::absdiff(im, prev, diff);
        im.copyTo(prev);
        //cout << countNonZero(diff) << endl;
    } while (cv::countNonZero(diff) > 10);
    
    im *= 255;
}