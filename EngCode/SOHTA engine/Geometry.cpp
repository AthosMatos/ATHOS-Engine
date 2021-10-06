#include "Geometry.h"

ID3D11BlendState* Geometry::BS_Transparent;
ID3D11BlendState* Geometry::BS_Opaque;
cbPerObject  Geometry::cbPerObj;
ID3D11Buffer* Geometry::cbPerObjectBuffer;
cbPerFrame Geometry::constbuffPerFrame;
ID3D11Buffer* Geometry::cbPerFrameBuffer;
ID3D11RasterizerState* Geometry::RS_Transparent2;
ID3D11RasterizerState* Geometry::RS_Transparent1;
SLight Geometry::lighT[];

XMVECTOR Geometry::rotyaxis;
XMVECTOR Geometry::rotzaxis;
XMVECTOR Geometry::rotxaxis;
ID3D11DepthStencilState* Geometry::DSLessEqual;

Geometry::Geometry()
{
    if (!CBuffers)CreateBuffers();
    if (!Rasterizers)Load_All_RasterizerStates();

    if (!Depht)Load_ALL_DepthStates();

    d3dDevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);   
}

void Geometry::Release()
{
    if (cbPerObjectBuffer) cbPerObjectBuffer->Release();
    if (cbPerFrameBuffer) cbPerFrameBuffer->Release();
    if (RS_Wireframe) try { RS_Wireframe->Release(); } catch(...){}
    if (BS_Transparent) BS_Transparent->Release();
    if (RS_Transparent1)RS_Transparent1->Release();
    if (RS_Transparent2) RS_Transparent2->Release();
    if (RS_Opaque) RS_Opaque->Release();

    sphereIndexBuffer->Release();
    sphereVertBuffer->Release();

    smrv->Release();

    DSLessEqual->Release();

    Shaders::Release();
}

void Geometry::CreateBuffers()
{
    D3D11_BUFFER_DESC cbbd;
    ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

    cbbd.Usage = D3D11_USAGE_DEFAULT;
    cbbd.ByteWidth = sizeof(cbPerObject);
    cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbbd.CPUAccessFlags = 0;
    cbbd.MiscFlags = 0;

    HRESULT  hr = d3dDevice->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);
    cbbd.ByteWidth = sizeof(cbPerFrame);
    hr = d3dDevice->CreateBuffer(&cbbd, NULL, &cbPerFrameBuffer);

    CBuffers = true;
}

void Geometry::Load_ALL_DepthStates()
{
    D3D11_DEPTH_STENCIL_DESC dssDesc;
    ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    dssDesc.DepthEnable = true;
    dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

    /////DEPTH STATE FOR WHEN THE PIXEL THAT IS ABOUT TO BE DRAWN IS AHEAD OR IN THE SAME DEPTH OF THE PIXEL BEHIND
    dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    d3dDevice->CreateDepthStencilState(&dssDesc, &DSLessEqual);

    /////DEPTH STATE FOR WHEN THE PIXEL THAT IS ABOUT TO BE DRAWN IS AHEAD OF THE PIXEL BEHIND
    dssDesc.DepthFunc = D3D11_COMPARISON_LESS;
    d3dDevice->CreateDepthStencilState(&dssDesc, &DSLess);

    Depht = true;

}

////////////////////////RASTERIZER STATES////////////////////////////
void Geometry::Load_All_RasterizerStates()
{
    Create_Rasterizer_Wireframe();
    Create_Rasterizer_Blending();
    Create_Rasterizer_Opaque();

    Rasterizers = true;
}

void Geometry::Create_Rasterizer_Wireframe()
{
	D3D11_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));

	wfdesc.FillMode = D3D11_FILL_WIREFRAME;
	wfdesc.CullMode = D3D11_CULL_NONE;
	HRESULT hr = d3dDevice->CreateRasterizerState(&wfdesc, &RS_Wireframe); 
}

void Geometry::Create_Rasterizer_Blending()
{
    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));

    D3D11_RENDER_TARGET_BLEND_DESC rtbd;
    ZeroMemory(&rtbd, sizeof(rtbd));

    rtbd.BlendEnable = true;
    rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
    rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
    rtbd.BlendOp = D3D11_BLEND_OP_ADD;
    rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
    rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
    rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.RenderTarget[0] = rtbd;

    d3dDevice->CreateBlendState(&blendDesc, &BS_Transparent);  

    D3D11_RASTERIZER_DESC cmdesc;
    ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));

    cmdesc.FillMode = D3D11_FILL_SOLID;
    cmdesc.CullMode = D3D11_CULL_BACK;

    cmdesc.FrontCounterClockwise = true;
    HRESULT hr = d3dDevice->CreateRasterizerState(&cmdesc, &RS_Transparent1);

    cmdesc.FrontCounterClockwise = false;
    hr = d3dDevice->CreateRasterizerState(&cmdesc, &RS_Transparent2);
}

void Geometry::Create_Rasterizer_Opaque()
{
    D3D11_RASTERIZER_DESC rastDesc;
    ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
    rastDesc.FillMode = D3D11_FILL_SOLID;
    rastDesc.CullMode = D3D11_CULL_NONE;

    d3dDevice->CreateRasterizerState(&rastDesc, &RS_Opaque);
}




