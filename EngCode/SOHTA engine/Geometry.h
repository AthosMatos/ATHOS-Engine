#pragma once
#include "ConstBuffers.h"
#include "D3D.h"
#include "Camera.h"
#include "Shaders.h"

class Geometry : protected D3D , public Camera , protected Shaders
{
public:
	Geometry();
	void Release();

private:
	void CreateBuffers();
	void Load_ALL_DepthStates();

private:
	bool CBuffers = false;
	bool Rasterizers = false;
	bool Depht = false;

/////////////////////////RASTERIZER STATES////////////////////////////////

private:
	void Load_All_RasterizerStates();
	void Create_Rasterizer_Wireframe();
	void Create_Rasterizer_Blending();
	void Create_Rasterizer_Opaque();

	UINT Color_numElements;
	UINT Tex_numElements;
	UINT light_numElements;

protected:
	static ID3D11BlendState* BS_Transparent;
	static ID3D11BlendState* BS_Opaque;

protected:
	ID3D11RasterizerState* RS_Wireframe;
	static ID3D11RasterizerState* RS_Transparent1;
	static ID3D11RasterizerState* RS_Transparent2;
	ID3D11RasterizerState* RS_Opaque;

	static ID3D11DepthStencilState* DSLessEqual;
	ID3D11DepthStencilState* DSLess;

protected:
	static cbPerObject cbPerObj;
	static ID3D11Buffer* cbPerObjectBuffer;
	static ID3D11Buffer* cbPerFrameBuffer;

	static SLight lighT[10];
	static cbPerFrame constbuffPerFrame;

	static XMVECTOR rotyaxis;
	static XMVECTOR rotzaxis;
	static XMVECTOR rotxaxis;

	ID3D11Buffer* sphereIndexBuffer;
	ID3D11Buffer* sphereVertBuffer;

	ID3D11ShaderResourceView* smrv;

	XMMATRIX Rotationx;
	XMMATRIX Rotationy;


private:
	friend class D2D;
	friend class Text2D;
	friend class Graphics;

};

