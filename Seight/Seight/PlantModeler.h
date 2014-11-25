#ifndef PlantModeler_H
#define PlantModeler_H

#include "stdafx.h"
#include "PhenotypicData.h"

#include "ISegment.h"
#include "defaultSegment.h"
#include "HSVSegment.h"

#include "IPerspectiveCorrect.h"
#include "defaultPerspectiveCorrect.h"

#include "IFilter.h"
#include "defaultFilter.h"

#include "IEdgeDetect.h"
#include "defaultEdgeDetect.h"
#include "SobelEdgeDetect.h"

#include "ISkeletonize.h"
#include "defaultSkeletonize.h"

#include <iostream>

using namespace std;

class PlantModeler
{
private:
	ISegment *segmentation;
	IPerspectiveCorrect *correction;
	IFilter *imageFiltering;
	IEdgeDetect *edgeDetection;
	ISkeletonize *skeletonization;
	int countTiller(); //Update return type and parameters based on what is needed
	double measureHeight(); //Update return type and parameters based on what is needed
	
public:
	
	enum Approach
	{
		APPROACH_A, APPROACH_B, APPROACH_C //rename to more descriptive identifiers
	};
	~PlantModeler();
	PlantModeler();
	void processImage(Mat image); //PhenotypicData
	static PlantModeler createApproach(Approach approach)
	{
		cout << "in create approach" << endl;

		PlantModeler *plantModeler = new PlantModeler;
		switch (approach)
		{
		case PlantModeler::APPROACH_A:
			plantModeler->segmentation = new HSVSegment;
			plantModeler->correction = new defaultPerspectiveCorrect;
			plantModeler->imageFiltering = new defaultFilter;
			plantModeler->edgeDetection = new SobelEdgeDetect;
			plantModeler->skeletonization = new defaultSkeletonize;
			cout << "in approach A" << endl;
			break;
		case PlantModeler::APPROACH_B:
			break;
		case PlantModeler::APPROACH_C:
			break;
		}

		return *plantModeler;
	}

};

#endif
