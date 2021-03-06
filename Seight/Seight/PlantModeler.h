#ifndef PlantModeler_H
#define PlantModeler_H

#include "stdafx.h"
#include "PhenotypicData.h"

#include "IPreprocess.h"
#include "defaultPreprocess.h"
#include "normalizeAdjustBrightnessAndContrastPreprocess.h"

#include "ISegment.h"
#include "defaultSegment.h"
#include "HSVSegment.h"
#include "YCrCbSegment.h"

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

#include "IHeightMeasure.h"
#include "EuclideanHeightMeasure.h"
#include "HeightMeasurer.h"

#include "TillerCount.h"

#include <iostream>

using namespace std;

class PlantModeler
{
private:
    ISegment *segmentation;
	IPreprocess *preprocess;
    IPerspectiveCorrect *correction;
    IFilter *imageFiltering;
    IEdgeDetect *edgeDetection;
    ISkeletonize *skeletonization;
    IPlantStructure *structure;
	TillerCount *tillerCount;
	IHeightMeasure *heightMeasure;
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
			case APPROACH_B: return "APPROACH_B"; break;
			case APPROACH_C: return "APPROACH_C"; break;
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
				plantModeler->correction = new defaultPerspectiveCorrect;
				plantModeler->preprocess = new defaultPreprocess;
				plantModeler->segmentation = new HSVSegment;
                plantModeler->edgeDetection = new defaultEdgeDetect;
                plantModeler->tillerCount = new TillerCount;
				plantModeler->skeletonization = new defaultSkeletonize;
				plantModeler->heightMeasure = new EuclideanHeightMeasure;
                break;
            case PlantModeler::APPROACH_B:
				plantModeler->correction = new defaultPerspectiveCorrect; // change to some other perspective correct
				plantModeler->preprocess = new defaultPreprocess;//cut and normalize CutAndNormalizePreprocess
				plantModeler->segmentation = new YCrCbSegment;
				plantModeler->edgeDetection = new defaultEdgeDetect;
				plantModeler->tillerCount = new TillerCount;
				plantModeler->skeletonization = new defaultSkeletonize;
				plantModeler->heightMeasure = new EuclideanHeightMeasure;
                break;
            case PlantModeler::APPROACH_C:
                plantModeler->correction = new defaultPerspectiveCorrect;
                plantModeler->preprocess = new normalizeAdjustBrightnessAndContrastPreprocess;
                plantModeler->segmentation = new HSVSegment;
                plantModeler->edgeDetection = new defaultEdgeDetect;
                plantModeler->tillerCount = new TillerCount;
                plantModeler->skeletonization = new defaultSkeletonize;
                plantModeler->heightMeasure = new HeightMeasurer;
                break;
        }
        
        return *plantModeler;
    }
    
};

#endif