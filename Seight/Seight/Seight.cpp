// Seight.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Plant.h"
#include "PlantDAO.h"
#include "SQLPlantDAO.h"
#include "PlantPhenotyper.h"
#include <windows.h>

using namespace std;

int main()
{
	PlantPhenotyper* plantPhenotyper = new PlantPhenotyper;
	plantPhenotyper->phenotype();

	cin.ignore();

	return 0;
}