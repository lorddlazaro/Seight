////#include "stdafx.h"
#include "PixelConverter.h"


PixelConverter::PixelConverter()
{
}


PixelConverter::~PixelConverter()
{
}

double PixelConverter::convertImagePixelstoCentimeter(Mat marker, int heightPixel)
{
    int conversion = getPixelConversionCentimeter(marker);
    double height = heightPixel / conversion;
    return height;
}

int PixelConverter::getPixelConversionCentimeter(Mat image)
{
	Mat marker, detectedMarker, dst;
	int height = 0;
    double heightOfMarker = 4.7625; //in centimeters
	int pixelConversion = 0;
    Rect markerRegion = Rect(0,0,image.cols, image.rows * 0.09);
    image = image(markerRegion);
	cvtColor(image, marker, CV_BGR2HSV);
    
    //imshow("marker", marker);
    //Segment COLOR CARD
	//FUSCHIA
	int minH = 140; int minS = 0; int minV = 0;
	int maxH = 180; int maxS = 255; int maxV = 255;

	Scalar red_min = Scalar(minH, minS, minV);
	Scalar red_max = Scalar(maxH, maxS, maxV);
	Mat mask;
	inRange(marker, red_min, red_max, mask);
	Mat result;
	image.copyTo(result, mask);
    //imwrite("/Users/elishajeremygonzales/Documents/Thesis/Seightv2/Seightv2/images/marker/0.PNG", result);
    //int factor = 3;
    //int r = result.rows / factor;
    //int s = result.cols / factor;
    //Mat resizedRes;
    //resize(result, resizedRes, Size(s, r),0,0,CV_INTER_AREA);
    //imshow("1", resizedRes);
    //waitKey(0);
    
    
    minH = 0; minS = 0; minV = 0;
    maxH = 30; maxS = 255; maxV = 255;
    red_min = Scalar(minH, minS, minV);
    red_max = Scalar(maxH, maxS, maxV);
    Mat mask2;
    inRange(marker, red_min, red_max, mask2);
    Mat red;
    image.copyTo(red, mask2);
    //imwrite("/Users/elishajeremygonzales/Documents/Thesis/Seightv2/Seightv2/images/marker/1.PNG", red);
    //Mat resizedRes1;
    //resize(red, resizedRes1, Size(s, r),0,0,CV_INTER_AREA);
    //imshow("2", resizedRes1);
    //waitKey(0);
    
    Mat markers;
    addWeighted(result, 1, red, 1, 1, markers);
    //imwrite("/Users/elishajeremygonzales/Documents/Thesis/Seightv2/Seightv2/images/marker/2.PNG", markers);
    //Mat resizedRes2;
    //resize(markers, resizedRes2, Size(s, r),0,0,CV_INTER_AREA);
    //imshow("3", resizedRes2);
    //waitKey(0);
    
    //waitKey(0);
	//Detect EDGE
	blur(result, detectedMarker, Size(3, 3));
	Canny(detectedMarker, detectedMarker, 128, 128*3, 3);
	dst.create(image.size(), image.type());
	dst = Scalar::all(0);
	image.copyTo(dst, detectedMarker);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	cvtColor(dst, dst, CV_BGR2GRAY);
	findContours(dst, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    
    RNG rng(12345);
    Mat drawing1 = Mat::zeros( dst.size(), CV_8UC3);
    //cout << "CONTOURS " << contours.size() << endl;
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( 255,255,255 );
        drawContours( drawing1, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }
    //resize(drawing1, resizedRes, Size(s, r),0,0,CV_INTER_AREA);
    //imshow("drawing", resizedRes);
    //waitKey(0);
    
    Mat drawing = Mat::zeros( dst.size(), CV_8UC3);
	int largest_area = 0, largest_contour_index = 0;
	Rect bounding_rect;
	for (int i = 0; i< contours.size(); i++) // iterate through each contour. 
	{
		double a = contourArea(contours[i], false);  //  Find the area of contour
		if (a>largest_area){
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour
			bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
		}
	}
    drawContours( drawing, contours, largest_contour_index, Scalar(255, 255, 255), 2, 8, hierarchy, 0, Point() );
    Mat contourDraw;
    //resize(drawing, resizedRes, Size(s, r),0,0,CV_INTER_AREA);
    //imshow("drawing", resizedRes);
    //waitKey(0);
	rectangle(image, bounding_rect, Scalar(0, 255, 0), 1, 8, 0);
	height = bounding_rect.height;

	//Compute Pixel
	pixelConversion = height / heightOfMarker;
    cout << "Pixels in 1 CM: " << pixelConversion << endl;
	return pixelConversion;
}