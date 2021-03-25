#pragma once
#include "Includes.h"

struct Cam
{
	const wchar_t* name;

	XMMATRIX WVP;
	XMMATRIX camView;
	XMMATRIX camProjection;
	XMMATRIX camRotationMatrix;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;

	XMVECTOR DefaultForward;
	XMVECTOR DefaultRight;
	XMVECTOR camForward;
	XMVECTOR camRight;

	float camPitch;
	float camYaw;

	bool FirstPerson;
	bool NoClip;

	void D_FR()
	{
		DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

		camPitch = 0.0f;
		camYaw = 0.0f;

		FirstPerson = false;
		NoClip = true;
	}

	Cam* next;
	Cam* prev;
};