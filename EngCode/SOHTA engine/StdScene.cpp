#include "StdScene.h"

#define LOG(var) cout<<var<<endl;

void StdScene::LoadScene()
{
    cout << "STARTING STD SCENE\n";

    camera = new Camera(nullptr);
    cam = L"CAM1";

    show_fps = false;
  
    pressflag.insert(pair<string, bool>("camSwitch", false));
    pressflag.insert(pair<string, bool>("fpsshowSwitch", false));
    pressflag.insert(pair<string, bool>("firstpersonSwitch", false));

    KeyState.insert(pair<string, bool>("F", false));

    camera->Create(L"CAM1");
    camera->Create(L"CAM2");
    camera->UseCam(cam);
    // camera->Set_FOV(50.0f);
    camera->SetFistPerson();

    GridGround = new Ground();
    cubes = new CubeS(nullptr);
    Lightcubes = new PL_Cubes();
    sky = new Sky();
    image = new Image();
    TXT = new Text2D;

    sky->CreateSky(L"skymaps//skymap.dds");
    cubes->CreateCube(L"C1", L"fodase", 1);
    cubes->CreateCube(L"C2", L"fodase", L"textures//texxture2.png");
    cubes->CreateCube(L"C3", L"fodase", L"textures//texxture.png");
    cubes->CreateCube(L"C4", L"fodase", L"textures//rocktexture.png");
    cubes->CreateCube(L"C5", L"fodase", L"textures//texxture23.png");
    cubes->CreateCube(L"C6", L"fodase", L"textures//texxture3.png");

    TXT->Create(L"FPS");
    TXT->Create(L"AlphaInfo");
    TXT->Create(L"Info");
    TXT->Create(L"cam");
    TXT->Create(L"FPorNC");

    TXT->Update(L"FPS", L"FPS:", 40.0f, 50, 500, D2D1::ColorF::Yellow, 0);
    TXT->Update(L"AlphaInfo", L"SOTHA engine Ultra_Alpha_Beta", 15.0f, 680, 520, D2D1::ColorF::White, 0);
    TXT->Update(L"FPorNC", L"FIRST PERSON VIEW", 30.0f, 100, 0, D2D1::ColorF::Red, 0);

    Lightcubes->CreateLight(L"L1");
    Lightcubes->CreateLight(L"L2");
    Lightcubes->CreateLight(L"L3");
    Lightcubes->CreateLight(L"L4");
    Lightcubes->CreateLight(L"L5");

    GridGround->CreateGround(L"GRD", L"textures//rocktexture.png");
    //image->Load(L"IMG_1", L"textures//texxture2.png");

    cout << "STD SCENE LOADED \n";
}

void StdScene::UpdateScene(double frametime, double FPS)
{  
    float lightIntensity = 2.6f;
    float LightRange = 8.0f;
    XMFLOAT4 AmbientIntensity = XMFLOAT4(0.04f, 0.04f, 0.04f, 1.0f);

    if (!KeyState["F"].isPressing && KeyState["F"].Pressed)
    {
        KeyState["F"].Pressed = false;
        if (KeyState["F"].toggle == 0) { camera->SetFistPerson();   TXT->Update(L"FPorNC", L"FIRST PERSON VIEW", 30.0f, 100, 0, D2D1::ColorF::Red, 0);}
        else if (KeyState["F"].toggle == 1) { camera->SetNoClip();   TXT->Update(L"FPorNC", L"NOCLIP VIEW", 30.0f, 100, 0, D2D1::ColorF::Red, 0);}
    }

    fps = FPS;
    
    if (show_fps)
    {
        TXT->Update(L"FPS", L"FPS:", FPS, 40.0f, 50, 500, D2D1::ColorF::Yellow, 0);
    }
   
    if (KeyState["F"].toggle == 0)  TXT->Update(L"Info", L"PRESS 'Z' TO SEE FPS\nPRESS 'O' TO CHANGE CAMERA\nPRESS 'F' TO GO TO NO CLIP ", 15.0f, 700, 10, D2D1::ColorF::White, 0);
    else if (KeyState["F"].toggle == 1)  TXT->Update(L"Info", L"PRESS 'Z' TO SEE FPS\nPRESS 'O' TO CHANGE CAMERA\nPRESS 'F' TO GO TO FIRST PERSON ", 15.0f, 700, 10, D2D1::ColorF::White, 0);

    TXT->Update(L"cam", cam, 30.0f, 0, 0, D2D1::ColorF::Red, 0);
    
    //image->Update(L"IMG_1", 0.5f,0,0,400,400);

    camera->Update(cam);

    ///rotation math circle wise
   
    sky->Update();

    GridGround->UpdateGround(L"GRD", 1);

    Lightcubes->Update(L"L1", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(7.0f,//x
                        0.0f,//y
                         5.0f),//z
        true, 0.4f,
        LightRange,XMFLOAT3(1.0f, 0.0f, 0.0f), lightIntensity,
        AmbientIntensity);

    Lightcubes->Update(L"L2", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(13.0f,//x
                         0.0f,//y
                          5.0f),//z
        true, 0.4f,
        LightRange,XMFLOAT3(0.0f, 1.0f, 0.0f), lightIntensity,
        AmbientIntensity);

    Lightcubes->Update(L"L3", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(10.0f,//x
                        0.0f,//y
                         8.0f),//z
        true, 0.4f,
        LightRange,XMFLOAT3(1.0f, 1.0f, 1.0f), lightIntensity,
        AmbientIntensity);

    Lightcubes->Update(L"L4", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(10.0f,//x
                        0.0f,//y
                         2.0f),//z
        true, 0.4f,
        LightRange, XMFLOAT3(0.0f, 0.0f, 1.0f), lightIntensity,
        AmbientIntensity);


    Lightcubes->Update(L"L5", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(0.0f,//x
                        6.0f,//y
                         4.0f),//z
        true, 0.4f,
        10.0f, XMFLOAT3(1.0f, 1.0f, 1.0f), 20.0f,
        AmbientIntensity);


    cubes->UpdateCube(L"C1", XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f), 0,
        false, XMFLOAT3(0.0f,//x
            0.0f,//y
            10.0f),//z
        true, 0.7f, false, false, true, false, true, true);

    cubes->UpdateCube(L"C2", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(0.0f,//x
                        0.0f,//y
                         5.0f),//z
        true, 1.0f, false, false, true, false, true, true);

    cubes->UpdateCube(L"C3", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(5.0f,//x
                        0.0f,//y
                         0.0f),//z
        true, 1.0f, false, false, true, false, true, true);

    cubes->UpdateCube(L"C4", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(10.0f,//x
                        0.0f,//y
                         5.0f),//z
        true, 1.0f, false, false, true, false, true, true);

    cubes->UpdateCube(L"C5", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(5.0f,//x
                        0.0f,//y
                         10.0f),//z
        true, 1.0f, false, false, true, false, true, true);

    cubes->UpdateCube(L"C6", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(5.0f,//x
                        0.0f,//y
                        -5.0f),//z
        true, 1.0f, true, false, true, true, true, true);
}

void StdScene::Renderscene()
{
    GridGround->RenderGround(L"GRD");

    sky->Render();
    cubes->RenderGroup(L"fodase");

    //image->Draw(L"IMG_1", true);

    Lightcubes->Render(L"L1");
    Lightcubes->Render(L"L2");   
    Lightcubes->Render(L"L3");
    Lightcubes->Render(L"L4");
    Lightcubes->Render(L"L5");

    if (show_fps) TXT->Render(L"FPS", true);
    else TXT->Render(L"FPS", false);
  
    Debug_info();

}

void StdScene::Release()
{
    sky->Release();
    image->Release();
    GridGround->Release();
    cubes->Release();
    Lightcubes->Release();
    if (TXT)TXT->Release();
    if (camera)camera->Release();
}

void StdScene::SceneInput(double frametime)
{
    DIMOUSESTATE mouseCurrState;
    BYTE keyboardState[256];

    DI.DIKeyboard->Acquire();
    DI.DIMouse->Acquire();

    DI.DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);
    
    DI.DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

    float speed = (double)15.0f * frametime;

    if (keyboardState[DIK_F] & 0x80 )
    {
        KeyState["F"].isPressing = true;
        if (!KeyState["F"].Pressed)
        {
            KeyState["F"].Pressed = !KeyState["F"].Pressed;

            if(KeyState["F"].toggle==0) KeyState["F"].toggle = 1;
            else if (KeyState["F"].toggle == 1) KeyState["F"].toggle = 0;
        }
    }
    else if (!(keyboardState[DIK_F] & 0x80))
    {
        KeyState["F"].isPressing = false;
    }
        
        

    if (keyboardState[DIK_O] & 0x80)
    {
        if (!pressflag["camSwitch"])
        {
            if (cam != L"CAM2")cam = L"CAM2";
            else cam = L"CAM1";

            camera->UseCam(cam);
        }
        pressflag["camSwitch"] = true;
    }
    else if (!(keyboardState[DIK_O] & 0x80)) pressflag["camSwitch"] = false;


    ///fps show flag
    if (keyboardState[DIK_Z] & 0x80)
    {
        if (!pressflag["fpsshowSwitch"])
        {
            if (!show_fps) show_fps = true;
            else if (show_fps) show_fps = false;
        }
        pressflag["fpsshowSwitch"] = true;
    }
    else if (!(keyboardState[DIK_Z] & 0x80))  pressflag["fpsshowSwitch"] = false;

    if (keyboardState[DIK_A] & 0x80)
    {
        DI.moveLeftRight -= speed;
    }
    if (keyboardState[DIK_D] & 0x80)
    {
        DI.moveLeftRight += speed;
    }
    if (keyboardState[DIK_W] & 0x80)
    {
        DI.moveBackForward += speed;
    }
    if (keyboardState[DIK_S] & 0x80)
    {
        DI.moveBackForward -= speed;
    }   
    if ((mouseCurrState.lX != DI.mouseLastState.lX) || (mouseCurrState.lY != DI.mouseLastState.lY))
    {   
        StdNoClipMouse(mouseCurrState);
        ShowMicePosDebug(false);

        DI.mouseLastState = mouseCurrState;
    }
   
    return;
}

void StdScene::StdNoClipMouse(DIMOUSESTATE mcs)
{
    DI.camYaw += (mcs.lX * 0.0001f) * sens; ///left right
    if ((int)((DI.camYaw * 10) * sens) >= 628 || (int)((DI.camYaw * 10) * sens) <= -628)
    {
        DI.camYaw = 0;///just to not acomulate numbers, this is a full 360 x wise
    }

    DI.camPitch2 += (mcs.lY * 0.0001f) * sens;
    if ((int)((DI.camPitch2 * 10) * sens) < 158 && (int)((DI.camPitch2 * 10) * sens) > -158)
    {
        DI.camPitch = DI.camPitch2;
    }
    else
    {
        DI.camPitch2 = DI.camPitch;
    }
}

void StdScene::ShowMicePosDebug(bool show)
{
    if (show)
    {
        ///debug shit
        cout << "LEFT RIGHT : " << (int)((DI.camYaw * 10) * sens) << endl;
        cout << "UP DOWN : " << (int)((DI.camPitch * 10) * sens) << endl;
    }   
}

void StdScene::Debug_info()
{   
    TXT->Render(L"AlphaInfo", true);
    TXT->Render(L"Info", true);
    TXT->Render(L"cam", true);
    TXT->Render(L"FPorNC", true);
}





