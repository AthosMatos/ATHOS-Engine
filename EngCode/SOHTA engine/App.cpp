#include "App.h"

App::App()
{
	ZeroMemory(&msg, sizeof(MSG));
    Gfx = new Graphics;
    window = new Win;
}

void App::StartApp(HINSTANCE hInstance)
{
    cout << "APP STARTED\n";
    window->StartWin(hInstance);
    Gfx->init(window->GetHwnd());
    Gfx->startScene();
    Dinput.InitDirectInput(window->GetHwnd(), hInstance);
    cout << "APP LOADED\n";
}

void App::RunApp()
{ 
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        frameCount++;

        if (timer.GetTime() >= 0.1f)
        {
            fps = frameCount*10; 
            frameCount = 0; 
            timer.StartTimer(); 
        }
        //Dinput.DetectInput(timer.GetFrameTime());         
        Gfx->Update(timer.GetFrameTime(), fps);
        Gfx->Render();

        if (Input())
        {
            break;
        }
    }
}

void App::EndApp()
{ 
    Gfx->Release();
    Dinput.Release();
    PostMessage(window->GetHwnd(), WM_DESTROY, 0, 0);
}

bool App::Input()
{
    BYTE keyboardState[256];

    Dinput.DIKeyboard->Acquire();

    Dinput.DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

    if (keyboardState[DIK_ESCAPE] & 0x80)
    {        
       // return true;
    }  
    return false;
}
