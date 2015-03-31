#include "stdafx.h"
#include "HeightMeasurer.h"


HeightMeasurer::HeightMeasurer()
{
}


HeightMeasurer::~HeightMeasurer()
{
}

float HeightMeasurer::perform(Mat image)
{
    float height = measureHeight(image);
    return height;
}

Mat skeleton;

Mat HeightMeasurer::getMarkedImage()
{
    return skeleton;
}

float HeightMeasurer::measureHeight(Mat image)
{
	cvtColor(image, skeleton, CV_GRAY2BGR);
	vector<Point> tiller;
	tiller.clear();
	
	//getTopPixel
	Point topPixel = getTopPixel();
	cout << topPixel.y << ", " << topPixel.x << endl;
	markPixel(topPixel);

	Point currentPixel = topPixel;
	tiller.push_back(currentPixel);
	cout << "Identifying tillers..." << endl;
	do
	{
		currentPixel = getNextPixel(currentPixel, tiller);
		tiller.push_back(currentPixel);
		markPixel(currentPixel);
        //cout<<".";
		
	} while (!(currentPixel.x == 0 && currentPixel.y == 0) && currentPixel.x != image.rows - 1);
    tiller.pop_back();
    cout <<endl;
    cout << "Done!" << endl;
    
    cout << "markedPixel " << tiller.size() << endl;
    
	//imwrite("E:/THESIS -Butil/Seightv2/Seightv2/images/heightImage/0.PNG", skeleton);
    
    double heightPixel = 0.0;
    /*** GETTING HEIGHT BY PIXEL COUNTING ONLY ***/
    //heightPixel = (int)tiller.size();
    
    
    /*** GETTING HEIGHT BY EUCLIDEAN DISTANCE ***/
    heightPixel = computeAllEuclideanDistance(tiller);

    int threshold = image.rows * .10;
    if(heightPixel < threshold)
    {
        Mat dupe;
        image.copyTo(dupe);
        
        cout <<  "til:" << tiller[tiller.size()-1].x << " cols:" << dupe.cols;
        cout << " row:" << dupe.rows - tiller[tiller.size()-1].x << endl;
        
        Rect rect = Rect(0, tiller[tiller.size()-1].x + 1, dupe.cols, dupe.rows - (tiller[tiller.size()-1].x + 1));
        
        //image.cols-5,(image.rows - tiller[tiller.size()-1].x-5));
        cout << "instantiated rect, ";
        dupe = dupe(rect);
        cout << "cropped dupe";
        heightPixel = measureHeight(dupe);
        cout << "just recursed"<<endl;
    }
    
	return heightPixel;
}

double HeightMeasurer::computeAllEuclideanDistance(vector<Point> tiller)
{
    double height = 0.0;
    
    //cout << "tiller size" << tiller.size() << endl;
    
    
    for (int i = 0; i < tiller.size(); i++) {
        if(i+1 != tiller.size())
        {
            double distance = 0;
            int x = abs(tiller[i].x - tiller[i+1].x);// cout << "x" << x << endl;
            int y = abs(tiller[i].y - tiller[i+1].y);// cout << "y" << y << endl;
            distance = pow(x, 2) + pow(y, 2);
            distance = sqrt(distance);
            height += distance;
            //cout << "x:" << tiller[i].x << " y:" << tiller[i].y << "x:" << tiller[i+1].x << " y:" << tiller[i+1].y << " X:" << x << " Y:" << y << " distance:" << distance <<endl;
        }
    }
    cout<< tiller.size() <<endl;
    cout << "Height ED: " << height << endl;
    return height;
}

Point HeightMeasurer::getTopPixel(){
	Point topPixel = Point(0,0);
	bool highestFound = false;

	for (int i = 0; i < skeleton.rows && !highestFound; i++)
	{
		for (int j = 0; j < skeleton.cols && !highestFound; j++)
		{
			Vec3b pixel = skeleton.at<Vec3b>(i, j);
			int b = pixel.val[0];
			int g = pixel.val[1];
			int r = pixel.val[2];
			if (b == 255 && g == 255 && r == 255){
				topPixel = Point(i, j);
				highestFound = true;
			}
		}
	}
	

	return topPixel;
}

bool isBound(int x, int y)
{
    if(x < 0 || y <0 || x > skeleton.rows || y>skeleton.cols){
        return false;
    }
    return true;
}

bool HeightMeasurer::isWhite(int x, int y)
{
    if (skeleton.at<Vec3b>(x, y).val[0] == 255 &&
        skeleton.at<Vec3b>(x, y).val[1] == 255 &&
        skeleton.at<Vec3b>(x, y).val[2] == 255)
        return true;
    else return false;
}

bool isLeft(int y)
{
    if (y < skeleton.cols/2)
        return true;
    return false;
}

Point HeightMeasurer::getNextPixel(Point currentPixel, vector<Point> previousPixels)
{
	Point nextPixel = Point(0,0);
	int x = currentPixel.x;
	int y = currentPixel.y;
	/***FOR DEBUGGING. REMOVE LATER.***
	cout << "1 ";
	int b = image.at<Vec3b>(x+1, y).val[0];
	int g = image.at<Vec3b>(x+1, y).val[1];
	int r = image.at<Vec3b>(x+1, y).val[2];
	cout << b << " + " << g << " + " << r << endl;

	cout << "2 ";
	 b = image.at<Vec3b>(x+1, y + 1).val[0];
	 g = image.at<Vec3b>(x+1, y + 1).val[1];
	 r = image.at<Vec3b>(x+1, y + 1).val[2];
	cout << b << " + " << g << " + " << r << endl;

	cout << "3 ";
	 b = image.at<Vec3b>(x+1, y - 1).val[0];
	 g = image.at<Vec3b>(x+1, y - 1).val[1];
	 r = image.at<Vec3b>(x, y + 1).val[2];
	cout << b << " + " << g << " + " << r << endl;

	cout << "x, y+1 == ";
	 b = image.at<Vec3b>(x, y + 1).val[0];
	 g = image.at<Vec3b>(x, y + 1).val[1];
	 r = image.at<Vec3b>(x, y + 1).val[2];
	cout << b << " + " << g << " + " << r << endl;

	cout << "x, y-1 == ";
	 b = image.at<Vec3b>(x, y - 1).val[0];
	 g = image.at<Vec3b>(x, y - 1).val[1];
	 r = image.at<Vec3b>(x, y - 1).val[2];
	cout << b << " + " << g << " + " << r << endl;
	******/
    bool isFound = false;
    int i = 1;
    int range = .01*skeleton.rows;
    
    if(isLeft(y))
    {
        while(!isFound && i<range)
        {
            int px = x + i;
            
            //check pivot
            if (isBound(px,y) && isWhite(px, y))
            {
                // cout << " 1 " << endl;
                nextPixel.x = px;
                nextPixel.y = y;
                isFound = true;
            }
            
            
            // check right from pivot
            if(!isFound)
            {
                for(int j=1; j<=i;j++)
                {
                    if(isBound(px,y+j) && isWhite(px, y+j))
                    {
                        nextPixel.x = px;
                        nextPixel.y = y+j;
                        isFound = true;
                    }
                }
            }
            
            
            //check left from pivot
            if(!isFound)
            {
                for(int j=1; j<=i;j++)
                {
                    if(isBound(px,y-j) && isWhite(px, y-j))
                    {
                        nextPixel.x = px;
                        nextPixel.y = y-j;
                        isFound = true;
                    }
                }
            }
            
            
            //check up from right of pivot
            if(!isFound)
            {
                for(int j=1; j<=i;j++)
                {
                    if(isBound(px-j,(y+i)) && isWhite(px-j,(y+i)))
                    {
                        nextPixel.x =px-j;
                        nextPixel.y = (y+i);
                        isFound = true;
                    }
                }
            }
            
            //check up from left of pivot
            if(!isFound)
            {
                for(int j=1; j<=i;j++)
                {
                    if(isBound(px-j,(y-i)) && isWhite(px-j,(y-i)))
                    {
                        nextPixel.x =px-j;
                        nextPixel.y = (y-i);
                        isFound = true;
                    }
                }
            }
            i++;
        }
        
//
//            
//            
//            
//            
//            
//            
//            //bottom
//            if ((x + i) != skeleton.rows && isWhite(x+i, y))
//            {
//                // cout << " 1 " << endl;
//                nextPixel.x = x + i;
//                nextPixel.y = y;
//                isFound = true;
//            }
//            //right bottom
//            else if ((y + i) != skeleton.cols && isWhite(x+i, y+i))
//            {
//                //cout << " 2 " << endl;
//                nextPixel.x = x + i;
//                nextPixel.y = y + i;
//                isFound = true;
//            }
//            //left bottom
//            else if (
//                     (x + i) != skeleton.rows &&
//                     (y - i) >= 0 && isWhite(x+i, y-i))
//            {
//                //cout << " 3 " << endl;
//                nextPixel.x = x + i;
//                nextPixel.y = y - i;
//                isFound = true;
//            }//right
//            else if (
//                     (y + i) != skeleton.cols && isWhite(x, y+i))
//            {
//                //cout << " 4 " << endl;
//                nextPixel.x = x;
//                nextPixel.y = y + i;
//                isFound = true;
//            }//left
//            else if ((y - i) >= 0 && isWhite(x, y-i))
//            {
//                //cout << " 5 " << endl;
//                nextPixel.x = x;
//                nextPixel.y = y - i;
//                isFound = true;
//            }
            
        

    }
    else
    {
        while(!isFound && i<range){
            int px = x + i;
            
            //check pivot
            if (isBound(px,y) && isWhite(px, y))
            {
                // cout << " 1 " << endl;
                nextPixel.x = px;
                nextPixel.y = y;
                isFound = true;
            }
            
            
            
            //check left from pivot
            if(!isFound)
            {
                for(int j=1; j<=i;j++)
                {
                    if(isBound(px,y-j) && isWhite(px, y-j))
                    {
                        nextPixel.x = px;
                        nextPixel.y = y-j;
                        isFound = true;
                    }
                }
            }
            
            // check right from pivot
            if(!isFound)
            {
                for(int j=1; j<=i;j++)
                {
                    if(isBound(px,y+j) && isWhite(px, y+j))
                    {
                        nextPixel.x = px;
                        nextPixel.y = y+j;
                        isFound = true;
                    }
                }
            }
            
            
            //check up from left of pivot
            if(!isFound)
            {
                for(int j=1; j<=i;j++)
                {
                    if(isBound(px-j,(y-i)) && isWhite(px-j,(y-i)))
                    {
                        nextPixel.x =px-j;
                        nextPixel.y = (y-i);
                        isFound = true;
                    }
                }
            }
            
            //check up from right of pivot
            if(!isFound)
            {
                for(int j=1; j<=i;j++)
                {
                    if(isBound(px-j,(y+i)) && isWhite(px-j,(y+i)))
                    {
                        nextPixel.x =px-j;
                        nextPixel.y = (y+i);
                        isFound = true;
                    }
                }
            }
            
            i++;
//            if ((x + i) != skeleton.rows && isWhite(x+i, y))
//            {
//                // cout << " 1 " << endl;
//                nextPixel.x = x + i;
//                nextPixel.y = y;
//                isFound = true;
//            }
//            else if (
//                     (x + i) != skeleton.rows &&
//                     (y - i) >= 0 && isWhite(x+i, y-i))
//            {
//                //cout << " 3 " << endl;
//                nextPixel.x = x + i;
//                nextPixel.y = y - i;
//                isFound = true;
//            }
//            else if ((y + i) != skeleton.cols && isWhite(x+i, y+i))
//            {
//                //cout << " 2 " << endl;
//                nextPixel.x = x + i;
//                nextPixel.y = y + i;
//                isFound = true;
//            }
//            else if ((y - i) >= 0 && isWhite(x, y-i))
//            {
//                //cout << " 5 " << endl;
//                nextPixel.x = x;
//                nextPixel.y = y - i;
//                isFound = true;
//            }
//            else if (
//                     (y + i) != skeleton.cols && isWhite(x, y+i))
//            {
//                //cout << " 4 " << endl;
//                nextPixel.x = x;
//                nextPixel.y = y + i;
//                isFound = true;
//            }
//            i++;
        }

    }
    
	return nextPixel;
}



void HeightMeasurer::markPixel(Point point)
{
	skeleton.at<Vec3b>(point.x, point.y).val[0] = 0;
	skeleton.at<Vec3b>(point.x, point.y).val[1] = 0;
	skeleton.at<Vec3b>(point.x, point.y).val[2] = 255;
}