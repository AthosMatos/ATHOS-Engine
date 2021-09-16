#pragma once
#include "ModelStrct.h"
#include <vector>

using namespace std;

class RQ
{
public:
	RQ();

public:
	void addToQueue(Model data);
	void UpdateModel(const wchar_t* ModelName, Model data);
	void RenderModel();
	void RenderAll();

private:

	static vector <Model> Queue;


};

