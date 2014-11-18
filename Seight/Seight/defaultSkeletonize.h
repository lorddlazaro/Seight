#pragma once

#ifndef defaultSkeletonize_H
#define defaultSkeletonize_H

#include "ISkeletonize.h"

class defaultSkeletonize : public ISkeletonize
{
public:
	defaultSkeletonize();
	~defaultSkeletonize();
	void perform();
};

#endif defaultSkeletonize_H