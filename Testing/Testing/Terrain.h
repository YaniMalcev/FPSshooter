#ifndef __TERRAIN_H__
#define __TERRAIN_H__
#include "Globalincludes.h"
#define TERRAIN_X			255
#define TERRAIN_Z			255
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)
struct CUSTOMVERTEX {FLOAT X, Y, Z; D3DVECTOR NORMAL;};
class Terrain
{
	
	LPDIRECT3DVERTEXBUFFER9	m_pTerrainVB;
	LPDIRECT3DINDEXBUFFER9	m_pTerrainIB;

	DWORD					m_dwTerrainVertices,
							m_dwTerrainPrimitives;
public:
	unsigned char** HeightMap;
							Terrain(LPDIRECT3DDEVICE9 d3ddev);

	void					CreateTerrain(LPDIRECT3DDEVICE9 d3ddev);

	void					Draw(LPDIRECT3DDEVICE9 d3ddev);


};
#endif