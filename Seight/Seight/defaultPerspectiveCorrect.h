#pragma once

#ifndef defaultPerspectiveCorrect_H
#define defaultPerspectiveCorrect_H

#include "IPerspectiveCorrect.h"

class defaultPerspectiveCorrect: public IPerspectiveCorrect
{
public:
	defaultPerspectiveCorrect();
	~defaultPerspectiveCorrect();
	Mat perform(Mat image);
};

#endif