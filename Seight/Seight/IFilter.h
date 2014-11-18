#ifndef IFilter_H
#define IFilter_H

#include "stdafx.h"

class IFilter
{
public:
	IFilter();
	~IFilter();
	virtual void perform();
};

#endif