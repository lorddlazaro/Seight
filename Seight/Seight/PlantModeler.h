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

#include "IPlantStructure.h"
#include "PlantStructure.h"

#include "TillerCount.h"

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
    IPlantStructure *structure;
    TillerCount *tillerCount;
    //int countTiller(Mat image); //Update return type and parameters based on what is needed
    double measureHeight(Mat skeleton); //Update return type and parameters based on what is needed

    
public:
    PlantModeler();
    ~PlantModeler();
    enum Approach
    {
        APPROACH_A, APPROACH_B, APPROACH_C //rename to more descriptive identifiers
    };
	static string getApproachString(Approach approach)
	{
		switch (approach)
		{
			case APPROACH_A: return "APPROACH_A"; break;
			case APPROACH_B: return "APPROACH_A"; break;
			case APPROACH_C: return "APPROACH_A"; break;
			default: return "Approach Name Default"; break;
		}
	}
    void processImage(Mat image, string name); //PhenotypicData
    static PlantModeler createApproach(Approach approach)
    {
		cout << "Creating Approach:" << getApproachString(approach) << endl;
        
        PlantModeler *plantModeler = new PlantModeler;
        switch (approach)
        {
            case PlantModeler::APPROACH_A:
                plantModeler->segmentation = new HSVSegment;
                plantModeler->correction = new defaultPerspectiveCorrect;
                plantModeler->imageFiltering = new defaultFilter;
                plantModeler->edgeDetection = new defaultEdgeDetect;
                plantModeler->skeletonization = new defaultSkeletonize;
                //plantModeler->structure = new PlantStructure;
                plantModeler->tillerCount = new TillerCount;
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