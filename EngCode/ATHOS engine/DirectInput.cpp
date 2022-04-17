#include "DirectInput.h"

float DirectInput::rotx = 0;
float DirectInput::rotz = 0;
float DirectInput::scaleX = 1.0f;
float DirectInput::scaleY = 1.0f;

float DirectInput::moveLeftRight = 0.0f;
float DirectInput::moveBackForward = 0.0f;

float DirectInput::camYaw = 0.0f;
float DirectInput::camPitch = 0.0f;
float DirectInput::camPitch2 = 0.0f;

int DirectInput::sens = 10;

DIMOUSESTATE DirectInput::mouseLastState;
DIMOUSESTATE DirectInput::mouseCurrState;

LPDIRECTINPUT8 DirectInput::directInput;

IDirectInputDevice8* DirectInput::DIKeyboard;
IDirectInputDevice8* DirectInput::DIMouse;

bool DirectInput::InitDirectInput(HWND hwnd, HINSTANCE hInstance)
{
    cout << "DIRECT INPUT STARTED\n";

    HRESULT hr = DirectInput8Create(hInstance,
        DIRECTINPUT_VERSION,
        IID_IDirectInput8,
        (void**)&directInput,
        NULL);

    hr = directInput->CreateDevice(GUID_SysKeyboard,
        &DIKeyboard,
        NULL);

    hr = directInput->CreateDevice(GUID_SysMouse,
        &DIMouse,
        NULL);

    hr = DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
    hr = DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

    hr = DIMouse->SetDataFormat(&c_dfDIMouse);
    hr = DIMouse->SetCooperativeLevel(hwnd,  DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

    cout << "DIRECT INPUT LOADED\n";

    return true;
}

void DirectInput::Release()
{
    DIKeyboard->Unacquire();
    DIMouse->Unacquire();
    directInput->Release();
}
