#pragma once

#ifndef defaultFilter_H
#define defaultFilter_H

#include "IFilter.h"

class defaultFilter : public IFilter
{
public:
	defaultFilter();
	~defaultFilter();
	void perform();
};

#endif defaultFilter_H
