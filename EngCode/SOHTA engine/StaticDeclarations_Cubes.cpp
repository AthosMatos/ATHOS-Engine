#include "Cubes.h"

Model* CubeS::cubes;
bool CubeS::Queueflag;
bool CubeS::debug_show_dist = false;
ID3D11Buffer* CubeS::CubeIndexBuffer;
ID3D11Buffer* CubeS::CubeVertBuffer_Tex_light;
ID3D11Buffer* CubeS::CubeVertBuffer_Tex;
ID3D11Buffer* CubeS::CubeVertBuffer_Color;
