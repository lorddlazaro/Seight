#pragma once

#ifndef defaultEdgeDetect_H
#define defaultEdgeDetect_H

#include "IEdgeDetect.h"

class defaultEdgeDetect : public IEdgeDetect
{
public:
	defaultEdgeDetect();
	~defaultEdgeDetect();
	//void thresh_callback(int value, void* userdata);
	void perform(Mat image);
};

#endif defaultEdgeDetect_H
