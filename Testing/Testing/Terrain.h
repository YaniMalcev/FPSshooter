#ifndef __TERRAIN_H__
#define __TERRAIN_H__
#include "Globalincludes.h"
#define TERRAIN_X			255
#define TERRAIN_Z			255
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
struct CUSTOMVERTEX {FLOAT X, Y, Z; D3DVECTOR NORMAL;FLOAT U,V;};
class Terrain
{
	
	LPDIRECT3DVERTEXBUFFER9	m_pTerrainVB;
	LPDIRECT3DINDEXBUFFER9	m_pTerrainIB;

	DWORD					m_dwTerrainVertices,
							m_dwTerrainPrimitives;
	LPDIRECT3DTEXTURE9 texture;
	void LoadHeighMap(char* hightmap);
	void LoadVertexBuffer(LPDIRECT3DDEVICE9 d3ddev);
	void LoadIndexBuffer(LPDIRECT3DDEVICE9 d3ddev);
public:
	unsigned char** HeightMap;
							Terrain(LPDIRECT3DDEVICE9 d3ddev);

	void					CreateTerrain(LPDIRECT3DDEVICE9 d3ddev);

	void					Draw(LPDIRECT3DDEVICE9 d3ddev);


};
#endif