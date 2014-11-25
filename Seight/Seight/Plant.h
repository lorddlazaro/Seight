#pragma once
#ifndef Plant_H
#define Plant_H

#include "stdafx.h"
#include <ctime>
#include <string>
#include <vector>

using namespace std;

class Plant
{
private:
	int id;
	string eventName;
	tm datePlaced;
	string plantStage;
	string plantType;
	string comments;
	//vector<Image> images;
public:
	Plant();
	~Plant();
};

#endif
