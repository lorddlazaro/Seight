#pragma once

#ifndef defaultFilter_H
#define defaultFilter_H

#include "IFilter.h"

class defaultFilter : public IFilter
{
public:
	defaultFilter();
	~defaultFilter();
	Mat perform(Mat image);
};

#endif
