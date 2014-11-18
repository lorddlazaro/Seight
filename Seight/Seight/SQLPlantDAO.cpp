#include "stdafx.h"
#include "SQLPlantDAO.h"

using namespace std;

SQLPlantDAO::SQLPlantDAO()
{
	cout << "constructing a new SQLPlantDAO" << endl;
}

void insertPlant(Plant &plant)
{
	cout << "delete in SQLPlantDAO" << endl;
}

void deletePlant(Plant plant)
{
	cout << "delete in SQLPlantDAO" << endl;
}

void updatePlant(Plant plant)
{
	cout << "update in SQLPlantDAO" << endl;
}
vector<Plant> getAllPlants()
{
	cout << "getting plants in SQLPlantDAO" << endl;
	vector<Plant> plants(5, Plant());
	return plants;
}

Plant getPlantbyId(int ID)
{
	cout << "getting plant (id) in SQLPlantDAO" << endl;
	Plant *plant = new Plant;
	return *plant;
}