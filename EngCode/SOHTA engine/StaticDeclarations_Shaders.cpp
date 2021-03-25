#include "Shaders.h"

ID3D11VertexShader* Shaders::VS_tex = NULL;
ID3D11VertexShader* Shaders::VS_cor = NULL;
ID3D11VertexShader* Shaders::VS_light = NULL;
ID3D11PixelShader* Shaders::PS_tex = NULL;
ID3D11PixelShader* Shaders::PS_clip_O = NULL;
ID3D11PixelShader* Shaders::PS_clip_T = NULL;
ID3D11PixelShader* Shaders::PS_cor = NULL;
ID3D11PixelShader* Shaders::PS_light = NULL;
ID3D11VertexShader* Shaders::SKYMAP_VS = NULL;
ID3D11PixelShader* Shaders::SKYMAP_PS = NULL;

ID3D11InputLayout* Shaders::vertLayout_tex = NULL;
ID3D11InputLayout* Shaders::vertLayout_cor = NULL;
ID3D11InputLayout* Shaders::vertLayout_light = NULL;
bool Shaders::Created = false;