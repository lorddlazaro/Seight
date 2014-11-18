#pragma once

#ifndef defaultEdgeDetect_H
#define defaultEdgeDetect_H

#include "IEdgeDetect.h"

class defaultEdgeDetect : public IEdgeDetect
{
public:
	defaultEdgeDetect();
	~defaultEdgeDetect();
	void perform();
};

#endif defaultEdgeDetect_H
