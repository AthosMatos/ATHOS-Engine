#pragma once
#include "Geometry.h"
#include "Timer.h"

class CubeS : protected Geometry
{
private:
	struct Cubes
	{
		const wchar_t* name;
		const wchar_t* GroupName;

		XMFLOAT3 color;
		int color_presets;

		XMMATRIX cubeWorld;
		XMMATRIX Rotation;
		XMMATRIX Scale;
		XMMATRIX Translation;
		
		bool ActivateTransparenry;
		bool ActivateWireframe;
		bool opaque;
		bool ActivatePixelcliping;
		bool ActivateLight;
		bool queued;

		float debug_disfcam;
		bool textured;
		ID3D11ShaderResourceView* Texture;
		ID3D11SamplerState* TexSamplerState;

		Cubes* next;
		Cubes* prev;

		float GetDistFromCam()
		{
			XMVECTOR cubePos = XMVectorZero();
			cubePos = XMVector3TransformCoord(cubePos, cubeWorld);

			float distX = XMVectorGetX(cubePos) - XMVectorGetX(camPosition);
			float distY = XMVectorGetY(cubePos) - XMVectorGetY(camPosition);
			float distZ = XMVectorGetZ(cubePos) - XMVectorGetZ(camPosition);

			return distX * distX + distY * distY + distZ * distZ;
		}
	};

	static Cubes* cubes;
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

	void Release();

private:
	Cubes* STDCubeCreate();
	void CreateIndexBuffer();
	void CreateVertexBuffer_Colored(int preset, float red, float green, float blue);
	void CreateVertexBuffer_Textured();
	void CreateVertexBuffer_light();
	void CreateTexture(Cubes* cubes, const wchar_t* texPath);

	void RenderTransparent();
	void RenderWireframe();
	void RenderOpaque();

	void StdQUEUE();
	void TransparencyQUEUE();
	static bool Queueflag;

	static bool debug_show_dist;

private:
	static ID3D11Buffer* squareIndexBuffer;
	static ID3D11Buffer* squareVertBuffer_Tex_light;
	static ID3D11Buffer* squareVertBuffer_Tex;
	static ID3D11Buffer* squareVertBuffer_Color;

	UINT stride_Tex_light;
	UINT stride_Tex;
	UINT stride_Color;

	UINT offset;

private:
	friend class D2D;
	friend class Light;
	friend class PL_Cubes;
};

