#include "win.h"
DirectInput DI;

LRESULT CALLBACK WndProc
(
    HWND hwnd,    //Default windows procedure
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
);

Win::Win()
{
	ClassName = L"Classi";
    hwnd = NULL;
}

void Win::StartWin(HINSTANCE hInstance)
{
    WClass(hInstance);

    hwnd = CreateWindowEx(    //Create our Extended Window
        NULL,    //Extended style
        ClassName,    //Name of our windows class
        L"SOTHA engine",    //Name in the title bar of our window
        WS_OVERLAPPEDWINDOW,    //style of our window
        CW_USEDEFAULT, CW_USEDEFAULT,    //Top left corner of window
        H_res,    //Width of our window
        V_res,    //Height of our window
        NULL,    //Handle to parent window
        NULL,    //Handle to a Menu
        hInstance,    //Specifies instance of current program
        NULL    //used for an MDI client window
    );

    if (!hwnd)    //Make sure our window has been created
    {
        //If not, display error
        MessageBox(NULL, L"Error creating window",
            L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(hwnd, SW_SHOW);    //Shows our window
    UpdateWindow(hwnd);    //Its good to update our window

    
}

HWND Win::GetHwnd()
{
    return hwnd;
}

void Win::WClass(HINSTANCE hInstance)
{
    WNDCLASSEX wc;    //Create a new extended windows class

    wc.cbSize = sizeof(WNDCLASSEX);    //Size of our windows class
    wc.style = CS_HREDRAW | CS_VREDRAW;    //class styles
    wc.lpfnWndProc = WndProc;    //Default windows procedure function
    wc.cbClsExtra = NULL;    //Extra bytes after our wc structure
    wc.cbWndExtra = NULL;    //Extra bytes after our windows instance
    wc.hInstance = hInstance;    //Instance to current application
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);    //Title bar Icon
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);    //Default mouse Icon
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);    //Window bg color
    wc.lpszMenuName = NULL;    //Name of the menu attached to our window
    wc.lpszClassName = ClassName;    //Name of our windows class
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); //Icon in your taskbar

    if (!RegisterClassEx(&wc))    //Register our windows class
    {
        //if registration failed, display error
        MessageBox(NULL, L"Error registering class",
            L"Error", MB_OK | MB_ICONERROR);
        return ;
    }

}

LRESULT CALLBACK WndProc
(
    HWND hwnd,    //Default windows procedure
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    float x = 0;
    float y = 0;

    DirectInput di;

    switch (msg)    //Check message
    {
        case WM_DESTROY:    //if x button in top right was pressed
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_SETFOCUS:
        {
            if (!(x || y))
            {              
                di.camPitch = 0.0f;
                di.camPitch2 = 0.0f;
                di.camYaw = 0.0f;
            }                  
        }
    }

    //return the message for windows to handle it
    return DefWindowProc(hwnd, msg,wParam,lParam);
}