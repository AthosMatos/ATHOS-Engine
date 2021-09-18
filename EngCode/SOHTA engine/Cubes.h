#pragma once
#include "Timer.h"
#include "ModelStrct.h"

class CubeS : protected Geometry
{
public:
	CubeS();
	CubeS(nullptr_t);

	void CreateCube(const wchar_t* CubeName, const wchar_t* texpath);
	void CreateCube(const wchar_t* CubeName, XMFLOAT3 color);
	void CreateCube(const wchar_t* CubeName, int colorPreset);

	void CreateCube(const wchar_t* CubeName, const wchar_t* GroupName, const wchar_t* texpath);
	void CreateCube(const wchar_t* CubeName, const wchar_t* GroupName, XMFLOAT3 color);
	void CreateCube(const wchar_t* CubeName, const wchar_t* GroupName, int colorPreset);

	XMMATRIX UpdateCube(const wchar_t* CubeName,
		XMVECTOR rotaxis, float rot,
		bool ActivateTranslation, XMFLOAT3 pos,
		bool ActivateScale, float size, 
		bool transparent, bool wireframe, bool opaque,bool pixelcliping,bool light);

	XMMATRIX GetWorld(const wchar_t* CubeName);
	void ChangeColor(const wchar_t* CubeName, XMFLOAT3 color);

	void RenderCube(const wchar_t* CubeName);
	void RenderGroup(const wchar_t* GroupName);

	ID3D11Buffer* getIndexBuffer();
	ID3D11Buffer* getVertBuffer(const wchar_t* type);

	void Release();

private:
	Model* STDCubeCreate();
	void CreateIndexBuffer();
	void CreateVertexBuffer_Colored(int preset, float red, float green, float blue);
	void CreateVertexBuffer_Textured();
	void CreateVertexBuffer_light();
	void CreateTexture(Model* cubes, const wchar_t* texPath);

	void RenderTransparent();
	void RenderWireframe();
	void RenderOpaque();

	void StdQUEUE();
	void TransparencyQUEUE();
	static bool Queueflag;

	static bool debug_show_dist;

private:
	static Model* cubes;
	static ID3D11Buffer* CubeIndexBuffer;
	static ID3D11Buffer* CubeVertBuffer_Tex_light;
	static ID3D11Buffer* CubeVertBuffer_Tex;
	static ID3D11Buffer* CubeVertBuffer_Color;

	UINT stride_Tex_light;
	UINT stride_Tex;
	UINT stride_Color;

	UINT offset;

private:
	friend class D2D;
	friend class Light;
	friend class PL_Cubes;
};

