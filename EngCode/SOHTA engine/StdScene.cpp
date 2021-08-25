#include "StdScene.h"

void StdScene::LoadScene()
{
    cout << "STARTING STD SCENE\n";

    GridGround = new Ground();
    cubes = new CubeS(nullptr);
    Lightcubes = new PL_Cubes();
    sky = new Sky();
    image = new Image();

    sky->CreateSky(L"skymaps//skymap.dds");
    cubes->CreateCube(L"C1", L"fodase", 1);
    cubes->CreateCube(L"C2", L"fodase", L"textures//texxture2.png");
    cubes->CreateCube(L"C3", L"fodase", L"textures//texxture.png");
    cubes->CreateCube(L"C4", L"fodase", L"textures//test.png");
    cubes->CreateCube(L"C5", L"fodase", L"textures//texxture23.png");
    cubes->CreateCube(L"C6", L"fodase", L"textures//texxture3.png");

    Lightcubes->CreateLight(L"L1");
    Lightcubes->CreateLight(L"L2");

    GridGround->CreateGround(L"GRD", L"textures//grid.png");
    image->Load(L"IMG_1", L"textures//texxture2.png");

    cout << "STD SCENE LOADED \n";
}

void StdScene::UpdateScene(double frametime, double FPS)
{  
    ///rotation math circle wise
    rot += 0.5f*frametime;
    if (rot > XM_2PI) rot = 0.0f;

    sky->Update();

    GridGround->UpdateGround(L"GRD", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(0.0f, //x
                       -4.0f, //y
                         0.0f),//z
        true, 2);

    Lightcubes->Update(L"L1", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(0.0f,//x
                        0.0f,//y
                         2.0f),//z
        true, 0.3f,
        6.0f, 
        XMFLOAT3(1.0f, 1.0f, 1.0f), 4.0f,
        XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));

    Lightcubes->Update(L"L2", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(13.0f,//x
                         0.0f,//y
                          5.0f),//z
        true, 0.4f,
        6.0f, 
        XMFLOAT3(1.0f, 0.3f, 0.5f), 6.0f,
        XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));

    cubes->UpdateCube(L"C1", XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f), 0,
        false, XMFLOAT3(0.0f,//x
                         0.0f,//y
                          10.0f),//z
        true, 0.7f, false, false, true, false, false);

    cubes->UpdateCube(L"C2", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(0.0f,//x
                        0.0f,//y
                         5.0f),//z
        true, 1.0f, true, false, false, false, true);

    cubes->UpdateCube(L"C3", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(5.0f,//x
                        0.0f,//y
                         0.0f),//z
        true, 1.0f, false, false, true, false, false);

    cubes->UpdateCube(L"C4", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(10.0f,//x
                        0.0f,//y
                         5.0f),//z
        true, 1.0f, false, false, true, false, true);

    cubes->UpdateCube(L"C5", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(5.0f,//x
                        0.0f,//y
                         10.0f),//z
        true, 1.0f, false, false, true, false, false);

    cubes->UpdateCube(L"C6", XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0,
        true, XMFLOAT3(5.0f,//x
                        0.0f,//y
                        -5.0f),//z
        true, 1.0f, true, false, true, true, false);
}

void StdScene::Renderscene()
{
    GridGround->RenderGround(L"GRD");

    sky->Render();

    cubes->RenderGroup(L"fodase");

    image->Draw(L"IMG_1",1.0f);

    Lightcubes->Render(L"L1");
    Lightcubes->Render(L"L2");
   
}

void StdScene::Release()
{
    sky->Release();
    image->Release();
    GridGround->Release();
    cubes->Release();
    Lightcubes->Release();
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





