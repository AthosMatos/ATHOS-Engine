#include "Camera.h"

XMMATRIX Camera::WVP;
XMMATRIX Camera::camView;
XMMATRIX Camera::camProjection;

XMVECTOR Camera::camPosition;
XMVECTOR Camera::camTarget;
XMVECTOR Camera::camUp;

Cam* Camera::CamHead;

const wchar_t* Camera::ActiveCam_name;
bool Camera::CamChange;