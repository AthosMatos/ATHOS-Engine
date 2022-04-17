#pragma once
#include "Includes.h"
#include "DirectInput.h"
#include "CameraStrct.h"
#include "VideoConfig.h"

#define stdFOV 100.0f

class Camera : VideoConfig
{
public:
	Camera(nullptr_t);
	Camera();

public:
	void Create(const wchar_t* name);
	void Update(const wchar_t* cam);
	void Remove(const wchar_t* cam);
	void Release();

	void UseCam(const wchar_t* cam);
	void SetFistPerson();
	void SetNoClip();
	void Set_FOV(float FOV);
	
private:
	void UpdateActiveCam();
	void StdCamPos();
	void UpdatePY(Cam* cam);  //PITCH AND YAW
	void UpdateFP(Cam* Tcam); //fist person
	void UpdateNC(Cam* Tcam); //no clip

protected:
	static XMMATRIX WVP;
	static XMMATRIX camView;
	static XMMATRIX camProjection;

public:
	static XMVECTOR camPosition;

protected:
	static XMVECTOR camTarget;
	static XMVECTOR camUp;

private:
	static const wchar_t* ActiveCam_name;
	static Cam* CamHead;

	static bool CamChange;

	DirectInput input;
};

