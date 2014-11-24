//#include "stdafx.h"
#include "IEdgeDetect.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


IEdgeDetect::IEdgeDetect()
{
}


IEdgeDetect::~IEdgeDetect()
{
}

Mat IEdgeDetect::sobelEdge(Mat bw){
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    Mat grad;
    
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;
    /// Gradient X
    cv::Sobel( bw, grad_x, ddepth, 1, 0, 1, scale, delta, BORDER_DEFAULT );
    //cv::imshow("Sobel X", grad_x);
    /// Gradient Y
    cv::Sobel( bw, grad_y, ddepth, 0, 1, 1, scale, delta, BORDER_DEFAULT );
    //cv::imshow("Sobel Y", grad_y);
    
    convertScaleAbs( grad_x, abs_grad_x );
    convertScaleAbs( grad_y, abs_grad_y );
    
    cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
    
    return grad;
    
}

Mat IEdgeDetect::perform(Mat img) //vector<int>
{
    Mat grad;
    grad = sobelEdge(img);
    cv::imshow("Sobel", grad);
    
    return grad;
    
    //returns sobel edge detection; should be passed through gaussian blur, grayscaled and threshold
}
