#include "Cubes.h"

CubeS::CubeS(){}

CubeS::CubeS(nullptr_t)
{
    debug_show_dist = false; //SHOW CUBES DISTANCE 
    cubes = NULL;
    CreateIndexBuffer();
    CreateVertexBuffer_light();
    CreateVertexBuffer_Textured();
    renderQueue=new RQ();
}

/////////////////////OVERLOADED CREATE FUNCTIONS/////////////////
void CubeS::CreateCube(const wchar_t* CubeName, const wchar_t* texpath)
{
    Model* Tcube;

    Tcube = STDCubeCreate();
    Tcube->name = CubeName;
    Tcube->textured = true;
    CreateTexture(Tcube, texpath);
}

void CubeS::CreateCube(const wchar_t* CubeName, XMFLOAT3 color)
{
    Model* Tcube;

    Tcube = STDCubeCreate();
    Tcube->name = CubeName;
    Tcube->textured = false;
    Tcube->color_presets = 0;
    Tcube->color = color;
     
}

void CubeS::CreateCube(const wchar_t* CubeName, int colorPreset)
{
    Model* Tcube;

    Tcube = STDCubeCreate();
    Tcube->name = CubeName;
    Tcube->textured = false;
    Tcube->color_presets = colorPreset;

}


void CubeS::CreateCube(const wchar_t* CubeName, const wchar_t* GroupName, const wchar_t* texpath)
{
    Model* Tcube;

    Tcube = STDCubeCreate();
    Tcube->name = CubeName;
    Tcube->GroupName = GroupName;
    Tcube->textured = true;
    CreateTexture(Tcube, texpath);
   
}

void CubeS::CreateCube(const wchar_t* CubeName, const wchar_t* GroupName, XMFLOAT3 color)
{
    Model* Tcube;

    Tcube = STDCubeCreate();
    Tcube->name = CubeName;
    Tcube->GroupName = GroupName;
    Tcube->textured = false;
    Tcube->color_presets = 0;
    Tcube->color = color;
}

void CubeS::CreateCube(const wchar_t* CubeName, const wchar_t* GroupName, int colorPreset)
{
    Model* Tcube;

    Tcube = STDCubeCreate();
    Tcube->name = CubeName;
    Tcube->GroupName = GroupName;
    Tcube->textured = false;
    Tcube->color_presets = colorPreset;

    //renderQueue
}



XMMATRIX CubeS::UpdateCube(const wchar_t* CubeName, XMVECTOR rotaxis, float rot, bool ActivateTranslation, XMFLOAT3 pos, bool ActivateScale, float size, bool transparent, bool wireframe, bool opaque, bool pixelcliping, bool light)
{
    Model* fcube;
    fcube = cubes;

    while (fcube->name != CubeName) { fcube = fcube->next; }

    fcube->modelWorld = XMMatrixIdentity();
    fcube->Translation = XMMatrixTranslation(pos.x / size, pos.y / size, pos.z / size);
    fcube->Scale = XMMatrixScaling(1.0f * size, 1.0f * size, 1.0f * size);
    fcube->Rotation = XMMatrixRotationAxis(rotaxis, rot);
    fcube->ActivateTransparenry = transparent;
    fcube->ActivateWireframe = wireframe;
    fcube->opaque = opaque;
    fcube->ActivatePixelcliping = pixelcliping;
    fcube->ActivateLight = light;

    if (ActivateTranslation == true && ActivateScale == true && rot == 0) fcube->modelWorld = fcube->Translation * fcube->Scale;
    else if (ActivateTranslation == true && ActivateScale == true && rot != 0)fcube->modelWorld = fcube->Translation * fcube->Rotation * fcube->Scale;
    else if (ActivateTranslation == true && ActivateScale == false && rot != 0) fcube->modelWorld = fcube->Translation * fcube->Rotation;
    else if (ActivateTranslation == true && ActivateScale == false && rot == 0) fcube->modelWorld = fcube->Translation;
    else if (ActivateTranslation == false && ActivateScale == true && rot != 0) fcube->modelWorld = fcube->Rotation * fcube->Scale;
    else if (ActivateTranslation == false && ActivateScale == true && rot == 0)fcube->modelWorld = fcube->Scale;
    else fcube->modelWorld = fcube->Rotation;   

    return fcube->modelWorld;
}

void CubeS::ChangeColor(const wchar_t* CubeName, XMFLOAT3 color)
{
    Model* fcube;
    fcube = cubes;

    while (fcube->name != CubeName) { fcube = fcube->next; }

    fcube->color = color;
}

void CubeS::CreateVertexBuffer_light()
{
    light_Vertex v[] =
    {
        // Front Face
        light_Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,-1.0f, -1.0f, -1.0f),
        light_Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f,-1.0f,  1.0f, -1.0f),
        light_Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f),
        light_Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f),

        // Back Face
        light_Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f),
        light_Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 1.0f),
        light_Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f),
        light_Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f,-1.0f,  1.0f, 1.0f),

        // Top Face
        light_Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,-1.0f, 1.0f, -1.0f),
        light_Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f,-1.0f, 1.0f,  1.0f),
        light_Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f),
        light_Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f),

        // Bottom Face
        light_Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f),
        light_Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f),
        light_Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, -1.0f,  1.0f),
        light_Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,-1.0f, -1.0f,  1.0f),

        // Left Face
        light_Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,-1.0f, -1.0f,  1.0f),
        light_Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,-1.0f,  1.0f,  1.0f),
        light_Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f,-1.0f,  1.0f, -1.0f),
        light_Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f),

        // Right Face
        light_Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f),
        light_Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, -1.0f),
        light_Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  1.0f),
        light_Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  1.0f),
    };

    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(light_Vertex) * 24;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexBufferData;

    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = v;
    HRESULT hr = d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &CubeVertBuffer_Tex_light);

    stride_Tex_light = sizeof(light_Vertex);
    offset = 0;
}

void CubeS::Release()
{
    if (CubeIndexBuffer)CubeIndexBuffer->Release();
    if (CubeVertBuffer_Tex)CubeVertBuffer_Tex->Release();
    if (CubeVertBuffer_Tex_light)CubeVertBuffer_Tex_light->Release();
    if (CubeVertBuffer_Color)CubeVertBuffer_Color->Release();

    Model* Temp = cubes;
    Model* TTemp;

    while (true)
    {
        if (Temp != NULL)
        {
            TTemp = Temp->next;
            free(Temp);
            Temp = TTemp;
        }
        else break;
    }
}

Model* CubeS::STDCubeCreate()
{
    if (cubes == NULL)
    {
        cubes = (Model*)malloc(sizeof(Model));

        cubes->Texture = NULL;
        cubes->TexSamplerState = NULL;
        cubes->queued = false;

        cubes->next = NULL;
        cubes->prev = NULL;

        return cubes;
    }
    else
    {
        Model* NewCube;
        NewCube = (Model*)malloc(sizeof(Model));

        NewCube->Texture = NULL;
        NewCube->TexSamplerState = NULL;
        NewCube->queued = false;

        NewCube->next = NULL;
   

        if (cubes->next == NULL)
        {
            cubes->next = NewCube;
            NewCube->prev = cubes;

            return NewCube;
        }
        else
        {
            while (cubes->next != NULL) { cubes = cubes->next; }
            cubes->next = NewCube;
            NewCube->prev = cubes;
            while (cubes->prev != NULL) { cubes = cubes->prev; }

            return NewCube;
        }
    }
    return NULL;
}

void CubeS::CreateIndexBuffer()
{
    DWORD indices[] = {
        // Front Face
        0,  1,  2,
        0,  2,  3,

        // Back Face
        4,  5,  6,
        4,  6,  7,

        // Top Face
        8,  9, 10,
        8, 10, 11,

        // Bottom Face
        12, 13, 14,
        12, 14, 15,

        // Left Face
        16, 17, 18,
        16, 18, 19,

        // Right Face
        20, 21, 22,
        20, 22, 23
    };

    D3D11_BUFFER_DESC indexBufferDesc;
    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(DWORD) * 12 * 3;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData;

    iinitData.pSysMem = indices;
    d3dDevice->CreateBuffer(&indexBufferDesc, &iinitData, &CubeIndexBuffer); 
}

void CubeS::CreateVertexBuffer_Colored(int preset, float red, float green, float blue)
{
    D3D11_SUBRESOURCE_DATA vertexBufferData;
    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));

    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(Colored_Vertex) * 24;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

    if (preset == 0)
    {
        Colored_Vertex v[] = //CUSTOM COLORED
        {
            // Front Face
                Colored_Vertex(-1.0f, -1.0f, -1.0f, red, green, blue, 1.0f),
                Colored_Vertex(-1.0f,  1.0f, -1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f,  1.0f, -1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f, -1.0f, -1.0f, red, green, blue, 1.0f),

                // Back Face
                Colored_Vertex(-1.0f, -1.0f, 1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f, -1.0f, 1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f,  1.0f, 1.0f, red, green, blue, 1.0f),
                Colored_Vertex(-1.0f,  1.0f, 1.0f, red, green, blue, 1.0f),

                // Top Face
                Colored_Vertex(-1.0f, 1.0f, -1.0f, red, green, blue, 1.0f),
                Colored_Vertex(-1.0f, 1.0f,  1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f, 1.0f,  1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f, 1.0f, -1.0f, red, green, blue, 1.0f),

                // Bottom Face
                Colored_Vertex(-1.0f, -1.0f, -1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f, -1.0f, -1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f, -1.0f,  1.0f, red, green, blue, 1.0f),
                Colored_Vertex(-1.0f, -1.0f,  1.0f, red, green, blue, 1.0f),

                // Left Face
                Colored_Vertex(-1.0f, -1.0f,  1.0f, red, green, blue, 1.0f),
                Colored_Vertex(-1.0f,  1.0f,  1.0f, red, green, blue, 1.0f),
                Colored_Vertex(-1.0f,  1.0f, -1.0f, red, green, blue, 1.0f),
                Colored_Vertex(-1.0f, -1.0f, -1.0f, red, green, blue, 1.0f),

                // Right Face
                Colored_Vertex(1.0f, -1.0f, -1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f,  1.0f, -1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f,  1.0f,  1.0f, red, green, blue, 1.0f),
                Colored_Vertex(1.0f, -1.0f,  1.0f, red, green, blue, 1.0f),
        };

        vertexBufferData.pSysMem = v;
    }
    else if (preset == 1)
    {
        Colored_Vertex v[] = //RGB PRESET
        {
            // Front Face
            Colored_Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
            Colored_Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
            Colored_Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
            Colored_Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),

            // Back Face
            Colored_Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
            Colored_Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
            Colored_Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
            Colored_Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),

            // Top Face
            Colored_Vertex(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
            Colored_Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
            Colored_Vertex(1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
            Colored_Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),

            // Bottom Face
            Colored_Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
            Colored_Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
            Colored_Vertex(1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f),
            Colored_Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f),

            // Left Face
            Colored_Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
            Colored_Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
            Colored_Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
            Colored_Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),

            // Right Face
            Colored_Vertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
            Colored_Vertex(1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
            Colored_Vertex(1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f),
            Colored_Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
        };

        vertexBufferData.pSysMem = v;
    }

    HRESULT hr = d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &CubeVertBuffer_Color);

    stride_Color = sizeof(Colored_Vertex);
    offset = 0;

    d3dDevCon->IASetVertexBuffers(0, 1, &CubeVertBuffer_Color, &stride_Color, &offset);
    CubeVertBuffer_Color->Release(); 
}

void CubeS::CreateVertexBuffer_Textured()
{
    Textured_Vertex v[] =
    {
        // Front Face
        Textured_Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Textured_Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
        Textured_Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
        Textured_Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

        // Back Face
        Textured_Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
        Textured_Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
        Textured_Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
        Textured_Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),

        // Top Face
        Textured_Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
        Textured_Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
        Textured_Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
        Textured_Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

        // Bottom Face
        Textured_Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
        Textured_Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Textured_Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
        Textured_Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),

        // Left Face
        Textured_Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
        Textured_Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
        Textured_Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
        Textured_Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

        // Right Face
        Textured_Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Textured_Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
        Textured_Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
        Textured_Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
    };


    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(Textured_Vertex) * 24;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexBufferData;

    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = v;
    HRESULT hr = d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &CubeVertBuffer_Tex);

    stride_Tex = sizeof(Textured_Vertex);
    offset = 0;   
}

void CubeS::CreateTexture(Model* cubes, const wchar_t* texPath)
{
    CreateWICTextureFromFile(d3dDevice, texPath, nullptr, &cubes->Texture, 0);

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    HRESULT hr = d3dDevice->CreateSamplerState(&sampDesc, &cubes->TexSamplerState);
}


void CubeS::RenderCube(const wchar_t* CubeName)
{
    bool flag = false;

    Model* fcube = cubes;

    while (fcube->name != CubeName) { fcube = fcube->next; }

    d3dDevCon->IASetIndexBuffer(CubeIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    if (debug_show_dist)
    {
        if (fcube->name != L"C4") //EXECPS C4 CAUSE ITS MOVING CONSTANTLY
        {
            if (fcube->GetDistFromCam() != fcube->debug_disfcam)
            {
                wstring ws(fcube->name);
                string str(ws.begin(), ws.end());

                fcube->debug_disfcam = fcube->GetDistFromCam();
                cout << str << "-" << (int)fcube->debug_disfcam << endl;

                flag = true;
            }
        }
    }

    if (fcube->textured)
    {
        if (fcube->ActivatePixelcliping)
        {
            if (fcube->ActivateLight)
            {
                for (int x = 0; x < 4; x++)
                {
                    constbuffPerFrame.light[x] = lighT[x];
                }

                d3dDevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &constbuffPerFrame, 0, 0);
                d3dDevCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);

                d3dDevCon->IASetVertexBuffers(0, 1, &CubeVertBuffer_Tex_light, &stride_Tex_light, &offset);

                //Set the Input Layout
                d3dDevCon->IASetInputLayout(vertLayout_light);

                d3dDevCon->VSSetShader(VS_light, 0, 0);
                d3dDevCon->PSSetShader(PS_clip_LT, 0, 0);
            }
            else
            {
                d3dDevCon->IASetVertexBuffers(0, 1, &CubeVertBuffer_Tex, &stride_Tex, &offset);

                //Set the Input Layout
                d3dDevCon->IASetInputLayout(vertLayout_tex);

                d3dDevCon->VSSetShader(VS_tex, 0, 0);
                d3dDevCon->PSSetShader(PS_clip_T, 0, 0);
            }
        }

        else if (fcube->ActivateLight)
        {
            ///THATS FOR A DINAMIC LIGHT, IN CASE OF A CONSTANT LIGHT I COULD JUST EXECUTE THIS ONCE AND NOT EVERY TIME I RENDER THE SCENE
            for (int x = 0; x < 4; x++)
            {
                constbuffPerFrame.light[x] = lighT[x];
            }

            d3dDevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &constbuffPerFrame, 0, 0);
            d3dDevCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);

            d3dDevCon->IASetVertexBuffers(0, 1, &CubeVertBuffer_Tex_light, &stride_Tex_light, &offset);
            d3dDevCon->PSSetShaderResources(0, 1, &fcube->Texture);
            d3dDevCon->PSSetSamplers(0, 1, &fcube->TexSamplerState);
            //Set the Input Layout
            d3dDevCon->IASetInputLayout(vertLayout_light);

            d3dDevCon->VSSetShader(VS_light, 0, 0);
            d3dDevCon->PSSetShader(PS_light, 0, 0);
        }
        else {

            d3dDevCon->IASetVertexBuffers(0, 1, &CubeVertBuffer_Tex, &stride_Tex, &offset);

            //Set the Input Layout
            d3dDevCon->IASetInputLayout(vertLayout_tex);

            d3dDevCon->VSSetShader(VS_tex, 0, 0);
            d3dDevCon->PSSetShader(PS_tex, 0, 0);
        }

        d3dDevCon->PSSetShaderResources(0, 1, &fcube->Texture);
        d3dDevCon->PSSetSamplers(0, 1, &fcube->TexSamplerState);
    }

    else
    {
        CreateVertexBuffer_Colored(fcube->color_presets, fcube->color.x, fcube->color.y, fcube->color.z);
        //Set the Input Layout
        d3dDevCon->IASetInputLayout(vertLayout_cor);

        d3dDevCon->VSSetShader(VS_cor, 0, 0);
        d3dDevCon->PSSetShader(PS_cor, 0, 0);
    }


    WVP = fcube->modelWorld * camView * camProjection;
    cbPerObj.World = XMMatrixTranspose(fcube->modelWorld);
    cbPerObj.WVP = XMMatrixTranspose(WVP);
    d3dDevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
    d3dDevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
    d3dDevCon->OMSetDepthStencilState(DSLess, 0);

    if (fcube->ActivateTransparenry) RenderTransparent();
    if (fcube->ActivateWireframe) RenderWireframe();
    if ((fcube->opaque) || (fcube->ActivatePixelcliping)) RenderOpaque();
}

void CubeS::RenderGroup(const wchar_t* GroupName)
{
    bool flag = false;

    StdQUEUE();

    Model* fcube = cubes;

    d3dDevCon->IASetIndexBuffer(CubeIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    while (true)
    {
        if (debug_show_dist)
        {
            if (fcube->name != L"C4") //EXECPS C4 COUSE ITS MOVING CONSTANTLY
            {
                if (fcube->GetDistFromCam() != fcube->debug_disfcam)
                {
                    wstring ws(fcube->name);
                    string str(ws.begin(), ws.end());

                    fcube->debug_disfcam = fcube->GetDistFromCam();
                    cout << str << "-" << (int)fcube->debug_disfcam << endl;

                    flag = true;
                }
            }
        }

        if (fcube->GroupName = GroupName)
        {
            if (fcube->textured)
            {
                if (fcube->ActivatePixelcliping)
                {
                    if (fcube->ActivateLight)
                    {
                        for (int x = 0; x < 4; x++)
                        {
                            constbuffPerFrame.light[x] = lighT[x];
                        }

                        d3dDevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &constbuffPerFrame, 0, 0);
                        d3dDevCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);

                        d3dDevCon->IASetVertexBuffers(0, 1, &CubeVertBuffer_Tex_light, &stride_Tex_light, &offset);

                        //Set the Input Layout
                        d3dDevCon->IASetInputLayout(vertLayout_light);

                        d3dDevCon->VSSetShader(VS_light, 0, 0);
                        d3dDevCon->PSSetShader(PS_clip_LT, 0, 0);
                    }
                    else
                    {
                        d3dDevCon->IASetVertexBuffers(0, 1, &CubeVertBuffer_Tex, &stride_Tex, &offset);

                        //Set the Input Layout
                        d3dDevCon->IASetInputLayout(vertLayout_tex);

                        d3dDevCon->VSSetShader(VS_tex, 0, 0);
                        d3dDevCon->PSSetShader(PS_clip_T, 0, 0);
                    }
                }

                else if (fcube->ActivateLight)
                {
                    ///THATS FOR A DINAMIC LIGHT, IN CASE OF A CONSTANT LIGHT I COULD JUST EXECUTE THIS ONCE AND NOT EVERY TIME I RENDER THE SCENE
                    for (int x = 0; x < 4; x++)
                    {
                        constbuffPerFrame.light[x] = lighT[x];
                    }

                    d3dDevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &constbuffPerFrame, 0, 0);
                    d3dDevCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);

                    d3dDevCon->IASetVertexBuffers(0, 1, &CubeVertBuffer_Tex_light, &stride_Tex_light, &offset);
                    d3dDevCon->PSSetShaderResources(0, 1, &fcube->Texture);
                    d3dDevCon->PSSetSamplers(0, 1, &fcube->TexSamplerState);
                    //Set the Input Layout
                    d3dDevCon->IASetInputLayout(vertLayout_light);

                    d3dDevCon->VSSetShader(VS_light, 0, 0);
                    d3dDevCon->PSSetShader(PS_light, 0, 0);
                }
                else {

                    d3dDevCon->IASetVertexBuffers(0, 1, &CubeVertBuffer_Tex, &stride_Tex, &offset);

                    //Set the Input Layout
                    d3dDevCon->IASetInputLayout(vertLayout_tex);

                    d3dDevCon->VSSetShader(VS_tex, 0, 0);
                    d3dDevCon->PSSetShader(PS_tex, 0, 0);
                }

                d3dDevCon->PSSetShaderResources(0, 1, &fcube->Texture);
                d3dDevCon->PSSetSamplers(0, 1, &fcube->TexSamplerState);
            }

            else
            {
                CreateVertexBuffer_Colored(fcube->color_presets, fcube->color.x, fcube->color.y, fcube->color.z);
                //Set the Input Layout
                d3dDevCon->IASetInputLayout(vertLayout_cor);

                d3dDevCon->VSSetShader(VS_cor, 0, 0);
                d3dDevCon->PSSetShader(PS_cor, 0, 0);
            }


            WVP = fcube->modelWorld * camView * camProjection;
            cbPerObj.World = XMMatrixTranspose(fcube->modelWorld);
            cbPerObj.WVP = XMMatrixTranspose(WVP);
            d3dDevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
            d3dDevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
            d3dDevCon->OMSetDepthStencilState(DSLess, 0);

            if (fcube->ActivateTransparenry) RenderTransparent();
            if (fcube->ActivateWireframe) RenderWireframe();
            if ((fcube->opaque) || (fcube->ActivatePixelcliping)) RenderOpaque();
        }
        if (fcube->next != NULL)
        {
            fcube = fcube->next;
        }
        else
        {
            break;
        }
    }
    if (flag == true)
    {
        cout << endl;
    }
}

ID3D11Buffer* CubeS::getIndexBuffer()
{
    return CubeIndexBuffer;
}

ID3D11Buffer* CubeS::getVertBuffer(const wchar_t* type)
{
    if (type == L"texture")
    {
        return CubeVertBuffer_Tex;
    }
    else if (type == L"light")
    {
        return CubeVertBuffer_Tex_light;
    }
    else if (type == L"color")
    {
        return CubeVertBuffer_Color;
    }
    else return NULL;

}

void CubeS::RenderTransparent()
{
    const float blendFactor[] = { 0.95f, 0.95f, 0.95f};
    d3dDevCon->OMSetBlendState(BS_Transparent, blendFactor, 0xffffffff);

    d3dDevCon->RSSetState(RS_Transparent1);
    d3dDevCon->DrawIndexed(36, 0, 0);

    d3dDevCon->RSSetState(RS_Transparent2);
    d3dDevCon->DrawIndexed(36, 0, 0);
}

void CubeS::RenderWireframe()
{
    d3dDevCon->OMSetBlendState(0, 0, 0xffffffff);
    d3dDevCon->RSSetState(RS_Wireframe);
    d3dDevCon->DrawIndexed(36, 0, 0);
}

void CubeS::RenderOpaque()
{
    d3dDevCon->OMSetBlendState(0, 0, 0xffffffff);
    d3dDevCon->RSSetState(RS_Opaque);
    d3dDevCon->DrawIndexed(36, 0, 0);
}

void CubeS::StdQUEUE()
{   
    Model* fcube;
    fcube = cubes;

    while (true)
    {
        if (fcube->ActivateTransparenry && !fcube->queued)
        {
            Model* Ncube=fcube;
            if (fcube->prev != NULL)fcube->prev->next = fcube->next;
            if (fcube->next != NULL)fcube->next->prev = fcube->prev;
            while (Ncube->next != NULL)Ncube = Ncube->next;

            Ncube->next = fcube;
            fcube->prev = Ncube;
            fcube->next = NULL;
            fcube->queued = true;

            while(fcube->prev!=NULL)fcube = fcube->prev;
        }      
        else
        {
            if (fcube->next != NULL)fcube = fcube->next;
            else
            {
                while (fcube->prev != NULL)fcube = fcube->prev;
                cubes = fcube;
                break;
            }        
        }
    }

    //cout << "queued" << endl;
    TransparencyQUEUE();
}

void CubeS::TransparencyQUEUE()
{
    Model* fcube=cubes;


    while (!fcube->ActivateTransparenry)
    {
        if (fcube->next != NULL)
        {
            fcube = fcube->next;
        }
        else return;       
    }
   
    Model* Ncube;
    if (fcube->next != NULL)Ncube = fcube;
    else return;

    while (true)
    {
        if (Ncube->next != NULL)Ncube = Ncube->next;
        else
        {
            if (fcube->next != NULL)
            {
                fcube = fcube->next;
                if (fcube->next != NULL)Ncube = fcube->next;
                else 
                { 
                    while (fcube->prev != NULL)fcube = fcube->prev; 
                    cubes = fcube;
                    break;
                };
            }
            else
            {
                while (fcube->prev != NULL)fcube = fcube->prev;
                cubes = fcube;
                break;
            }
        }

        if (fcube->GetDistFromCam() < Ncube->GetDistFromCam())
        {
            if (fcube->next == Ncube)
            {
                fcube->next = Ncube->next;
                Ncube->next = fcube;
                Ncube->prev = fcube->prev;
                Ncube->prev->next = Ncube;
                fcube->prev = Ncube;
                if(fcube->next!=NULL)fcube->next->prev = fcube;

                Model* Temp = fcube;
                fcube = Ncube;
                Ncube = Temp;
            }
            else 
            {
                Model* FCN = fcube->next;
                Model* FCP = fcube->prev;

                fcube->next = Ncube->next;
                fcube->prev = Ncube->prev;
                if (fcube->next != NULL)fcube->next->prev = fcube;
                fcube->prev->next = fcube;
                Ncube->next = FCN;
                Ncube->prev = FCP;
                Ncube->next->prev = Ncube;
                Ncube->prev->next = Ncube;

                FCN = fcube;
                fcube = Ncube;
                Ncube = FCN;
            }
        }
    }
}         





