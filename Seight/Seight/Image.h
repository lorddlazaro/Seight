#pragma once
#ifndef Image_H
#define Image_H

#include "PhenotypicData.h"
#include "Plant.h"
#include <ctime>

using namespace std;

class Plant;
class Image
{
private:
	int id;
	Plant plant;
	tm dateTaken; //not yet clear on what data type date is in c++
	string rawPath;
	string plantStage;
	string preprocessedHeightPath;
	string preprocessedGreennessPath;
	string preprocessedTillerCountPath;
	string preprocessedBiomassPath;
	PhenotypicData phenotypicData;
public:
	Image();
	~Image();
};

#endif
