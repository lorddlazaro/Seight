#ifndef SQLPlantDAO_H
#define SQLPlantDAO_H

#include "stdafx.h"
#include "PlantDAO.h"

using namespace std;

class SQLPlantDAO: public PlantDAO
{
private:
	vector<Plant> plants;
	Plant plant;
public:
	SQLPlantDAO();
	void insertPlant(Plant &plant){}
	void deletePlant(Plant plant){}
	void updatePlant(Plant plant){}
	vector<Plant> getAllPlants(){ return plants; }
	Plant getPlantbyId(int ID){ return plant; }
};

#endif