#pragma once
#include "ModelStrct.h"

class Ground : private Geometry
{	
public:
	Ground();

	void CreateGround(const wchar_t* GrdName, const wchar_t* texpath);
	void UpdateGround(const wchar_t* GrdName, int size);
	void RenderGround(const wchar_t* GrdName);
	void Release();

private:
	void CreateGrdIndexBuffer();
	void CreateVertexBuffer_Grd();
	void CreateVertexBuffer_Grd_Light();
	void CreateTexture(ModelStruct* grd, const wchar_t* texPath);

private:
	static ModelStruct* grd;

	static ID3D11Buffer* squareIndexBuffer;
	static ID3D11Buffer* squareVertBuffer;

	UINT stride;
	UINT offset;
};

