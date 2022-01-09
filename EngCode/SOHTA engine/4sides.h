#pragma once
#include "RenderQueue_2D.h"

class fourSides : RenderQueue_2D
{

public:
	void Create(const wchar_t* ID);
	void Update(const wchar_t* name, int left, int top, int right, int bottom);
	void Render(const wchar_t* name);

};