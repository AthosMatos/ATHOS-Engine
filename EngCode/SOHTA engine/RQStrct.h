#pragma once
#include "CubesStrct.h"
#include "GroundStrct.h"
#include "ImageStrct.h"
#include "Text2DStrct.h"

struct RenderQueue
{
	const wchar_t* name;

	XMMATRIX GeometryWorld;

	bool ActivateTransparenry;

	bool queued;
	int pos;

	float GetDistFromCam()
	{
		XMVECTOR cubePos = XMVectorZero();
		cubePos = XMVector3TransformCoord(cubePos, GeometryWorld);

		float distX = XMVectorGetX(cubePos) - XMVectorGetX(Camera::camPosition);
		float distY = XMVectorGetY(cubePos) - XMVectorGetY(Camera::camPosition);
		float distZ = XMVectorGetZ(cubePos) - XMVectorGetZ(Camera::camPosition);

		return distX * distX + distY * distY + distZ * distZ;
	}

	RenderQueue* next;
	RenderQueue* prev;
};