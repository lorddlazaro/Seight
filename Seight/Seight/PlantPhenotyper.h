
#include <string>
#include "PlantModeler.h"

class PlantPhenotyper
{
private:
	PlantModeler plantModeler;
public:
	PlantPhenotyper();
	~PlantPhenotyper();
	int phenotype();
	static string getExeDir();
};