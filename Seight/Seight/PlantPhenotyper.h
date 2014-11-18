#ifndef PlantPhenotyper_H
#define PlantPhenotyper_H

#include "PlantModeler.h"

class PlantPhenotyper
{
private:
	PlantModeler plantModeler;
public:
	PlantPhenotyper();
	~PlantPhenotyper();
	int phenotype();
};

#endif