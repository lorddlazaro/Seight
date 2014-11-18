#ifndef PlantDAO_H
#define PlantDAO_H

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Plant.h"

using namespace std;

class PlantDAO
{
private:
	vector<Plant> plants;
	Plant plant;
public:
	PlantDAO();
	virtual void insertPlant(Plant &plant) = 0;
	virtual void deletePlant(Plant plant) = 0;
	virtual void updatePlant(Plant plant) = 0;
	virtual vector<Plant> getAllPlants() = 0;
	virtual Plant getPlantbyId(int ID) = 0;

};

#endif
