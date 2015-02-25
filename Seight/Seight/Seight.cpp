// Seight.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Plant.h"
#include "PlantDAO.h"
#include "SQLPlantDAO.h"
#include "PlantPhenotyper.h"

using namespace std;

int main()
{
	
	//PlantDAO* plantDAO = new SQLPlantDAO;
	//Plant* plant = new Plant;
	//(*plantDAO).insertPlant(*plant);


	//get new plants
	PlantPhenotyper* plantPhenotyper = new PlantPhenotyper;
	plantPhenotyper->phenotype(/*list of plants*/);
	cin.ignore();

	return 0;
}

