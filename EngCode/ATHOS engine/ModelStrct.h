#pragma once
#include "Geometry.h"

struct ModelStruct
{
	//STD MODEL PROPRETIES
	const wchar_t* name;
	const wchar_t* GroupName = L"nogroup";

	XMFLOAT3 color;
	int color_presets = 0; //Colorfull cube

	XMMATRIX modelWorld;
	XMMATRIX Rotation;
	XMMATRIX Scale;
	XMMATRIX Translation;

	bool render = true;
	bool ActivateTransparenry = false;
	bool queued = false;
	bool ActivateWireframe = false;
	bool opaque = true;
	bool ActivatePixelcliping = false;
	bool ActivateLight = true;

	float debug_disfcam;
	bool textured = false;
	ID3D11ShaderResourceView* Texture;
	ID3D11SamplerState* TexSamplerState;

	bool ActivateTranslation = true;
	bool ActivateScale = true;
	int rot = 0;

	ModelStruct* next;
	ModelStruct* prev;

	int size; ///ground propretie


	float GetDistFromCam()
	{
		XMVECTOR cubePos = XMVectorZero();
		cubePos = XMVector3TransformCoord(cubePos, modelWorld);

		float distX = XMVectorGetX(cubePos) - XMVectorGetX(Camera::camPosition);
		float distY = XMVectorGetY(cubePos) - XMVectorGetY(Camera::camPosition);
		float distZ = XMVectorGetZ(cubePos) - XMVectorGetZ(Camera::camPosition);

		return distX * distX + distY * distY + distZ * distZ;
	}
};
