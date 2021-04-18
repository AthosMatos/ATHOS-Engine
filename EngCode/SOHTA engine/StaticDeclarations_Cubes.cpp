#include "Cubes.h"

Cubes* CubeS::cubes;
bool CubeS::Queueflag;
bool CubeS::debug_show_dist = false;
ID3D11Buffer* CubeS::squareIndexBuffer;
ID3D11Buffer* CubeS::squareVertBuffer_Tex_light;
ID3D11Buffer* CubeS::squareVertBuffer_Tex;
ID3D11Buffer* CubeS::squareVertBuffer_Color;
