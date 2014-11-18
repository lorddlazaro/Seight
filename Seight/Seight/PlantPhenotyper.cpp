#include "stdafx.h"
#include "PlantPhenotyper.h"
#include "PlantModeler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

PlantPhenotyper::PlantPhenotyper()
{
	cout << "creating approach in plant phenotyper constructor" << endl;
	PlantPhenotyper::plantModeler = PlantModeler::createApproach(PlantModeler::APPROACH_A);
}


PlantPhenotyper::~PlantPhenotyper()
{
}

int PlantPhenotyper::phenotype()
{
	Mat image;
	image = imread("D:/DE LA SALLE UNIVERSITY/Work/Thesis/Seight/Seight/Seight/image/IR64-012_.JPG", CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	
	Size size(350, 526);
	resize(image, image, size);
	
	namedWindow("Raw Image", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Raw Image", image);
	waitKey(3000);

	PlantPhenotyper::plantModeler.processImage(image);

	return 1;
}