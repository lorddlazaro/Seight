#pragma once

#ifndef defaultPreprocess_H
#define defaultPreprocess_H

#include "IPreprocess.h"

class defaultPreprocess : public IPreprocess
{
public:
	defaultPreprocess();
	~defaultPreprocess();
	Mat perform(Mat image);
};

#endif