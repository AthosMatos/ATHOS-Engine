#pragma once
#include "RQStrct.h"

class RQ
{
public:
	void Queue(const wchar_t* name, bool ActivateTransparenry, XMMATRIX GeometryWorld);
	void Organize();
	void Render();

private:

	void TransparencyOrganize();

	static RenderQueue* Q;

};

