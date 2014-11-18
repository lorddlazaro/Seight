#ifndef PhenotypicData_H
#define PhenotypicData_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class PhenotypicData
{
private:
	int id;
	Mat image;
	double height;
	int tillerCount;
	double greenness;
	double diameter;
	double Biomass;
public:
	PhenotypicData();
	~PhenotypicData();
};

#endif