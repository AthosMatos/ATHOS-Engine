#include "Shaders.h"

Shaders::Shaders()
{
    if (!Created)
    {
        Load_All_Shaders();
        Load_All_Layouts();

        Created = true;
        cout << "Shaders Loaded" << endl;
    }
}

void Shaders::Release()
{
    if (VS_Buffer_tex)VS_Buffer_tex->Release();
    if (PS_Buffer_cor)PS_Buffer_cor->Release();
    if (VS_tex)VS_tex->Release();
    if (PS_tex)PS_tex->Release();

    if (VS_Buffer_cor)VS_Buffer_cor->Release();
    if (PS_Buffer_tex)PS_Buffer_tex->Release();
    if (VS_cor)VS_cor->Release();
    if (PS_cor)PS_cor->Release();

    if (vertLayout_light) vertLayout_light->Release();
    if (vertLayout_tex) vertLayout_tex->Release();
    if (vertLayout_cor) vertLayout_cor->Release();

    SKYMAP_VS->Release();
    SKYMAP_PS->Release();
    SKYMAP_VS_Buffer->Release();
    SKYMAP_PS_Buffer->Release();
}

void Shaders::Load_All_Shaders()
{
    Create_VextexShader_Textured();
    Create_PixelShader_Textured();

    Create_VextexShader_Colored();
    Create_PixelShader_Colored();

    Create_VextexShader_light();
    Create_PixelShader_light();

    Create_PixelShader_Clipped();

    Create_PixelShader_SkyBox();
    Create_VextexShader_SkyBox();
}

void Shaders::Load_All_Layouts()
{
    Create_ColorLayout();
    Create_TexLayout();
    Create_LightLayout();
}


void Shaders::Create_VextexShader_Textured()
{
    HRESULT hr = D3DCompileFromFile(texture_shader_path, 0, 0, "VS", "vs_4_0", 0, 0, &VS_Buffer_tex, 0);
    hr = d3dDevice->CreateVertexShader(VS_Buffer_tex->GetBufferPointer(), VS_Buffer_tex->GetBufferSize(), NULL, &VS_tex);
}

void Shaders::Create_PixelShader_Textured()
{
    HRESULT hr = D3DCompileFromFile(texture_shader_path, 0, 0, "PS", "ps_4_0", 0, 0, &PS_Buffer_tex, 0);
    hr = d3dDevice->CreatePixelShader(PS_Buffer_tex->GetBufferPointer(), PS_Buffer_tex->GetBufferSize(), NULL, &PS_tex);
}

void Shaders::Create_VextexShader_Colored()
{
    HRESULT hr = D3DCompileFromFile(color_shader_path, 0, 0, "VS", "vs_4_0", 0, 0, &VS_Buffer_cor, 0);
    hr = d3dDevice->CreateVertexShader(VS_Buffer_cor->GetBufferPointer(), VS_Buffer_cor->GetBufferSize(), NULL, &VS_cor);
}

void Shaders::Create_PixelShader_Colored()
{
    HRESULT hr = D3DCompileFromFile(color_shader_path, 0, 0, "PS", "ps_4_0", 0, 0, &PS_Buffer_cor, 0);
    hr = d3dDevice->CreatePixelShader(PS_Buffer_cor->GetBufferPointer(), PS_Buffer_cor->GetBufferSize(), NULL, &PS_cor);
}

void Shaders::Create_VextexShader_light()
{
    HRESULT hr = D3DCompileFromFile(light_Textured_shader_path, 0, 0, "VS", "vs_4_0", 0, 0, &VS_Buffer_light, 0);
    hr = d3dDevice->CreateVertexShader(VS_Buffer_light->GetBufferPointer(), VS_Buffer_light->GetBufferSize(), NULL, &VS_light);
}

void Shaders::Create_PixelShader_Clipped()
{
    HRESULT hr = D3DCompileFromFile(cliped_opaque_texture_shader_path, 0, 0, "PS", "ps_4_0", 0, 0, &PS_Buffer_clip, 0);
    hr = d3dDevice->CreatePixelShader(PS_Buffer_clip->GetBufferPointer(), PS_Buffer_clip->GetBufferSize(), NULL, &PS_clip_O);

    hr = D3DCompileFromFile(cliped_transparent_texture_shader_path, 0, 0, "PS", "ps_4_0", 0, 0, &PS_Buffer_clip, 0);
    hr = d3dDevice->CreatePixelShader(PS_Buffer_clip->GetBufferPointer(), PS_Buffer_clip->GetBufferSize(), NULL, &PS_clip_T);
}

void Shaders::Create_PixelShader_SkyBox()
{

    D3DCompileFromFile(L"shaders//skyshader.fx", 0, 0, "SKYMAP_PS", "ps_4_0", 0, 0, &SKYMAP_PS_Buffer, 0);
    d3dDevice->CreatePixelShader(SKYMAP_PS_Buffer->GetBufferPointer(), SKYMAP_PS_Buffer->GetBufferSize(), NULL, &SKYMAP_PS);
}

void Shaders::Create_VextexShader_SkyBox()
{
    D3DCompileFromFile(L"shaders//skyshader.fx", 0, 0, "SKYMAP_VS", "vs_4_0", 0, 0, &SKYMAP_VS_Buffer, 0);
    d3dDevice->CreateVertexShader(SKYMAP_VS_Buffer->GetBufferPointer(), SKYMAP_VS_Buffer->GetBufferSize(), NULL, &SKYMAP_VS);
}

void Shaders::Create_TexLayout()
{
    D3D11_INPUT_ELEMENT_DESC Texlayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    UINT Tex_numElements = ARRAYSIZE(Texlayout);


    HRESULT hr = d3dDevice->CreateInputLayout(Texlayout, Tex_numElements, VS_Buffer_tex->GetBufferPointer(),
        VS_Buffer_tex->GetBufferSize(), &vertLayout_tex);
}

void Shaders::Create_ColorLayout()
{
    D3D11_INPUT_ELEMENT_DESC colorlayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT Color_numElements = ARRAYSIZE(colorlayout);

    HRESULT hr = d3dDevice->CreateInputLayout(colorlayout, Color_numElements, VS_Buffer_cor->GetBufferPointer(),
        VS_Buffer_cor->GetBufferSize(), &vertLayout_cor);
}

void Shaders::Create_LightLayout()
{
    D3D11_INPUT_ELEMENT_DESC lightlayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT light_numElements = ARRAYSIZE(lightlayout);

    HRESULT hr = d3dDevice->CreateInputLayout(lightlayout, light_numElements, VS_Buffer_light->GetBufferPointer(),
        VS_Buffer_light->GetBufferSize(), &vertLayout_light);
}

void Shaders::Create_PixelShader_light()
{
    HRESULT hr = D3DCompileFromFile(light_Textured_shader_path, 0, 0, "PS", "ps_4_0", 0, 0, &PS_Buffer_light, 0);
    hr = d3dDevice->CreatePixelShader(PS_Buffer_light->GetBufferPointer(), PS_Buffer_light->GetBufferSize(), NULL, &PS_light);
}
