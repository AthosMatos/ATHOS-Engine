#pragma once
#include "Cubes.h"
#include "DirectInput.h"

class PL_Cubes : private CubeS
{
protected:
	struct LightSource
	{
		const wchar_t* name;

		LightSource* next;
		LightSource* prev;
	};
	static LightSource* LS;

public:
	PL_Cubes();
	void CreateLight(const wchar_t* lightname);
	void Release();
	void Select(const wchar_t* ID);
	void Update(const wchar_t* lightname, XMVECTOR rotaxis, float rot, 
				bool ActivateTranslation, XMFLOAT3 pos, 
				bool ActivateScale, float size, 
				float range, 
				XMFLOAT3 color, float intensity, 
				XMFLOAT4 ambient);

	void Update(XMVECTOR rotaxis, float rot,
				bool ActivateTranslation, XMFLOAT3 pos,
				bool ActivateScale, float size, 
				float range, 
				XMFLOAT3 color, float intensity,
				XMFLOAT4 ambient);

private:
	void UpdateLight(LightSource* fLS, int x, float range, XMFLOAT4 ambient, XMFLOAT4 diffuse);

public:
	void Render(const wchar_t* lightname);
	void Render();

private:
	const wchar_t* Selected_Light;
	XMMATRIX Cwrld;

	static ID3D11Buffer* squareIndexBuffer;
	static ID3D11Buffer* squareVertBuffer;
};

