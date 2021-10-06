#include "PL_Cubes.h"

PL_Cubes::LightSource* PL_Cubes::LS;
ID3D11Buffer* PL_Cubes::squareIndexBuffer;
ID3D11Buffer* PL_Cubes::squareVertBuffer;

PL_Cubes::PL_Cubes()
{
    LS = NULL;
    Selected_Light = NULL;
}

void PL_Cubes::CreateLight(const wchar_t* lightname)
{
    if (LS == NULL)
    {
        //light
        LS = (LightSource*)malloc(sizeof(LightSource));
        LS->name = lightname;
        LS->next = NULL;
        LS->prev = NULL;

        //lightcube
        CubeS::CreateCube(lightname, XMFLOAT3(1.0f,1.0f,1.0f));

        return;
    }
    else
    {
        LightSource* NLS;
        NLS = (LightSource*)malloc(sizeof(LightSource));
        NLS->name = lightname;
        NLS->next = NULL;

        CubeS::CreateCube(lightname, XMFLOAT3(1.0f, 1.0f, 1.0f));
      
        if (LS->next == NULL)
        {
            NLS->prev = LS;
            LS->next = NLS;
            return;
        }
        else
        {
            while (LS->next != NULL) { LS = LS->next; }
            NLS->prev = LS;
            LS->next = NLS;
            while (LS->prev != NULL) { LS = LS->prev; }

            return;
        }
    }
}

void PL_Cubes::Select(const wchar_t* ID)
{
    Selected_Light = ID;
}

void PL_Cubes::Update(const wchar_t* lightname, XMVECTOR rotaxis, float rot,
                    bool ActivateTranslation, XMFLOAT3 pos,
                    bool ActivateScale, float size, 
                    float range, XMFLOAT3 color, float intensity, XMFLOAT4 ambient)
{
    LightSource* fLS;
    fLS = LS;
    int x = 0;

    while (true)
    {
        if (fLS->name != lightname)
        {
            if (fLS->next != NULL) { fLS = fLS->next; x++; }
            else { cout << "POINTLIGHT UPDATE:NOT FOUND"; return; }
        }
        else break;
    }
    CubeS::ChangeColor(lightname, color);
    Cwrld = CubeS::UpdateCube(lightname, rotaxis, rot, ActivateTranslation, pos, ActivateScale, size, false, false, true, false, false, true);
    UpdateLight(fLS, x, range, XMFLOAT4(color.x * intensity, color.y * intensity, color.z * intensity, 1.0f), ambient);
}

void PL_Cubes::Update(XMVECTOR rotaxis, float rot,
                    bool ActivateTranslation, XMFLOAT3 pos, 
                    bool ActivateScale, float size,
                    float range, XMFLOAT3 color, float intensity, XMFLOAT4 ambient)
{
    LightSource* fLS;
    fLS = LS;
    int x = 0;

    while (true)
    {
        if (fLS->name != Selected_Light)
        {
            if (fLS->next != NULL) { fLS = fLS->next; x++; }
            else { cout << "POINTLIGHT UPDATE:NOT FOUND"; return; }
        }
        else break;
    }

    CubeS::ChangeColor(Selected_Light, color);
    Cwrld = CubeS::UpdateCube(Selected_Light, rotaxis, rot, ActivateTranslation, pos, ActivateScale, size, false, false, true, false, false, true);
    UpdateLight(fLS, x, range, XMFLOAT4(color.x * intensity, color.y * intensity, color.z * intensity, 1.0f), ambient);
}


void PL_Cubes::UpdateLight(LightSource* fLS, int x, float range, XMFLOAT4 diffuse , XMFLOAT4 ambient)
{ 
    XMVECTOR lightVector = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

    lightVector = XMVector3TransformCoord(lightVector, Cwrld);

    lighT[x].pos.x = XMVectorGetX(lightVector);
    lighT[x].pos.y = XMVectorGetY(lightVector);
    lighT[x].pos.z = XMVectorGetZ(lightVector);

    lighT[x].range = range;
    lighT[x].att = XMFLOAT3(0.0f, 0.2f, 0.0f);
    lighT[x].ambient = ambient;
    lighT[x].diffuse = diffuse;
}

void PL_Cubes::Render(const wchar_t* lightname)
{
    LightSource* fLS;
    fLS = LS;

    while (true)
    {
        if (fLS->name != lightname)
        {
            if (fLS->next != NULL) fLS = fLS->next;
            else { cout << "POINTLIGHT UPDATE:NOT FOUND"; return; }
        }
        else break;
    } 

    CubeS::RenderCube(lightname);
}

void PL_Cubes::Render()
{
    LightSource* fLS;
    fLS = LS;
    while (true)
    {
        if (fLS->name != Selected_Light)
        {
            if (fLS->next != NULL) fLS = fLS->next;
            else { cout << "POINTLIGHT UPDATE:NOT FOUND"; return; }
        }
        else break;
    }
    CubeS::RenderCube(Selected_Light);
}

void PL_Cubes::Release()
{
    LightSource* Temp_LS = LS;
    LightSource* TTemp;

    if (squareVertBuffer)squareVertBuffer->Release();
    if (squareIndexBuffer)squareIndexBuffer->Release();

    while (true)
    {
        if (Temp_LS != NULL)
        {
            TTemp = Temp_LS->next;
            free(Temp_LS);
            Temp_LS = TTemp;
        }
        else break;
    }
}

