#pragma once
#include "Geometry.h"

struct Model
{
	//STD MODEL PROPRETIES
	const wchar_t* name;
	const wchar_t* GroupName;

	XMFLOAT3 color;
	int color_presets;

	XMMATRIX modelWorld;
	XMMATRIX Rotation;
	XMMATRIX Scale;
	XMMATRIX Translation;

	bool ActivateTransparenry;
	bool queued;
	bool ActivateWireframe;
	bool opaque;
	bool ActivatePixelcliping;
	bool ActivateLight;

	float debug_disfcam;
	bool textured;
	ID3D11ShaderResourceView* Texture;
	ID3D11SamplerState* TexSamplerState;

	bool ActivateTranslation;
	bool ActivateScale;
	int rot;

	Model* next;
	Model* prev;

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
