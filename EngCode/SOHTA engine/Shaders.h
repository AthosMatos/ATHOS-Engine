#pragma once
#include "D3D.h"

#define color_shader_path L"shaders//EffectsColor.fx"
#define texture_shader_path L"shaders//EffectsTexture.fx"
#define light_Textured_shader_path L"shaders//EffectsLight.fx"
#define cliped_opaque_texture_shader_path L"shaders//EffectsTextureClipped_Opaque.fx"
#define cliped_transparent_texture_shader_path L"shaders//EffectsTextureClipped_Transparent.fx"


class Shaders : private D3D
{
public:
	Shaders();
	void Release();

private:
	void Load_All_Shaders();
	void Load_All_Layouts();

	void Create_VextexShader_Textured();
	void Create_PixelShader_Textured();

	void Create_VextexShader_Colored();
	void Create_PixelShader_Colored();

	void Create_VextexShader_light();
	void Create_PixelShader_light();

	void Create_PixelShader_Clipped();

	void Create_PixelShader_SkyBox();
	void Create_VextexShader_SkyBox();

private:
	void Create_TexLayout();
	void Create_ColorLayout();
	void Create_LightLayout();

protected:
	static ID3D11PixelShader* PS_tex;
	static ID3D11VertexShader* VS_tex;

	static ID3D11PixelShader* PS_cor;
	static ID3D11VertexShader* VS_cor;

	static ID3D11PixelShader* PS_light;
	static ID3D11VertexShader* VS_light;
	
	static ID3D11PixelShader* PS_clip_O;
	static ID3D11PixelShader* PS_clip_T;

	static ID3D11VertexShader* SKYMAP_VS;
	static ID3D11PixelShader* SKYMAP_PS;
	
protected:
	static ID3D11InputLayout* vertLayout_tex;
	static ID3D11InputLayout* vertLayout_cor;
	static ID3D11InputLayout* vertLayout_light;

private:
	ID3D10Blob* VS_Buffer_tex;
	ID3D10Blob* VS_Buffer_cor;
	ID3D10Blob* VS_Buffer_light;

	ID3D10Blob* PS_Buffer_tex;
	ID3D10Blob* PS_Buffer_cor;
	ID3D10Blob* PS_Buffer_clip;
	ID3D10Blob* PS_Buffer_light;

	ID3D10Blob* SKYMAP_VS_Buffer;
	ID3D10Blob* SKYMAP_PS_Buffer;

	static bool Created;

private:
	friend class CubeS;
	friend class Text;
	friend class Ground;
	friend class Sky;
};

