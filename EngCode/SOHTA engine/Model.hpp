#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Includes.h"
#include "Geometry.h"
#include "ShaderStrct_Vertex.h"

using namespace std;

class Model : Geometry
{

private:
	struct SurfaceMaterial
	{
		wstring matName;
		XMFLOAT4 difColor;
		int texArrayIndex;
		bool hasTexture;
		bool transparent;
	};

public:
	bool LoadObjModel(wstring filename,
		bool isRHCoordSys,
		bool computeNormals);

	void loadTex(wstring filename);

	void Update();
	void Render();

	void CleanUp();


private:
	void loadTransparency();


private:
	ID3D11BlendState* Transparency;

	ID3D11Buffer* vertBuff;
	ID3D11Buffer* indexBuff;
	XMMATRIX meshWorld;
	int meshSubsets = 0;
	vector<int> subsetIndexStart;
	vector<int> subsetMaterialArray;
	ID3D11ShaderResourceView* Texture;
	ID3D11SamplerState* TexSamplerState;

	vector<ID3D11ShaderResourceView*> meshSRV;
	vector<wstring> textureNameArray;
	vector<SurfaceMaterial> material;
};

