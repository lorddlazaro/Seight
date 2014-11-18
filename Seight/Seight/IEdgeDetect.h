#ifndef IEdgeDetect_H
#define IEdgeDetect_H

#include "stdafx.h"
#include <vector>

using namespace std;

class IEdgeDetect
{
public:
	IEdgeDetect();
	~IEdgeDetect();
	virtual void perform(); //vector<int>
};

#endif
