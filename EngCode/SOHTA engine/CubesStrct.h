#pragma once
#include "Geometry.h"

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

		float distX = XMVectorGetX(cubePos) - XMVectorGetX(Camera::camPosition);
		float distY = XMVectorGetY(cubePos) - XMVectorGetY(Camera::camPosition);
		float distZ = XMVectorGetZ(cubePos) - XMVectorGetZ(Camera::camPosition);

		return distX * distX + distY * distY + distZ * distZ;
	}
};