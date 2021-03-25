#pragma once
#include "Geometry.h"

class Ground : private Geometry
{
private:
	struct GRD
	{
		const wchar_t* name;

		XMMATRIX World;
		XMMATRIX Rotation;
		XMMATRIX Scale;
		XMMATRIX Translation;

		int size;

		ID3D11ShaderResourceView* Texture;
		ID3D11SamplerState* TexSamplerState;

		GRD* next;
		GRD* prev;

	};
	static GRD* grd;

public:
	Ground();

	void CreateGround(const wchar_t* GrdName, const wchar_t* texpath);
	void UpdateGround(const wchar_t* GrdName,
		XMVECTOR rotaxis, float rot,
		bool ActivateTranslation, XMFLOAT3 pos,
		bool ActivateScale, int size);
	void RenderGround(const wchar_t* GrdName);
	void Release();

private:
	void CreateGrdIndexBuffer();
	void CreateVertexBuffer_Grd();
	void CreateTexture(GRD* grd, const wchar_t* texPath);

	static ID3D11Buffer* squareIndexBuffer;
	static ID3D11Buffer* squareVertBuffer;

	UINT stride;
	UINT offset;
};

