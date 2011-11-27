#include "Globalincludes.h"
#include "Terrain.h"


Terrain::Terrain(LPDIRECT3DDEVICE9& d3ddev)
{
m_pTerrainVB = NULL;
m_pTerrainIB = NULL;

m_dwTerrainVertices = (TERRAIN_X + 1) * (TERRAIN_Z + 1);
m_dwTerrainPrimitives = TERRAIN_X * TERRAIN_Z * 2;
HeightMap=NULL;
CreateTerrain(d3ddev);
texture=NULL;
	 D3DXCreateTextureFromFile(d3ddev,    // the Direct3D device
                              (LPCSTR)"Grass_2.png",    // the filename of the texture
                              &texture);    // the address of the texture storage
	 if(texture==NULL) ::MessageBoxW(NULL, L"Failed creating vertex declaration", L"Failed", MB_OK);
}//CTerrain


void Terrain::LoadHeighMap(char* hightmap){

ifstream File;

//load height information from file
File.open(hightmap,ios::binary);
HeightMap = new unsigned char*[TERRAIN_X + 1];
for(unsigned x = 0;x < (TERRAIN_X + 1);++x)
 {
	HeightMap[x] = new unsigned char[TERRAIN_X + 1];
 for(unsigned z = 0;z < (TERRAIN_Z + 1);++z)
  {
  HeightMap[x][z] = File.get();
  }
 }

File.close();
}

void Terrain::LoadVertexBuffer(LPDIRECT3DDEVICE9& d3ddev){
CUSTOMVERTEX* pVertexData;

//create vertex buffer and fill in vertcies
d3ddev->CreateVertexBuffer(m_dwTerrainVertices * sizeof(CUSTOMVERTEX),0,CUSTOMFVF,D3DPOOL_MANAGED,&m_pTerrainVB,NULL);
m_pTerrainVB->Lock(0,0,(void**)&pVertexData,0);

for(int x = 0;x < (TERRAIN_X + 1);++x)
  { 
	for(int z = 0;z < (TERRAIN_Z + 1);++z)
	{
		pVertexData[x + z * (TERRAIN_X + 1)].X = (float)x;
		pVertexData[x + z * (TERRAIN_X + 1)].Y = (float)HeightMap[x][z]/3;
		pVertexData[x + z * (TERRAIN_X + 1)].Z = (float)z;
		pVertexData[x + z * (TERRAIN_X + 1)].U = (float)((int)x%2);
		pVertexData[x + z * (TERRAIN_X + 1)].V = (float)((int)z%2);
	}
 }

//Light up the terrain
for(int x = 0;x < (TERRAIN_X);++x)
{ 
	for(int z = 0;z < (TERRAIN_Z + 1);++z)
	{
		float heightA = (float)HeightMap[x][z]/2;
		float heightB = (float)HeightMap[x][z+1]/2;
		float heightC = (float)HeightMap[x+1][z]/2;
		D3DXVECTOR3 u(1.0f, heightB - heightA, 0.0f);
		D3DXVECTOR3 v(0.0f, heightC - heightA, -1.0f);
		D3DXVECTOR3 n;
		D3DXVec3Cross(&n, &u, &v);
		D3DXVec3Normalize(&n, &n);
		pVertexData[x + z * (TERRAIN_X + 1)].NORMAL = n;
	}
}
  
 m_pTerrainVB->Unlock();

}

void Terrain::LoadIndexBuffer(LPDIRECT3DDEVICE9& d3ddev){

short* pIndexData=0;
//create index buffer and fill in indices
d3ddev->CreateIndexBuffer(sizeof(short) * m_dwTerrainPrimitives * 3,0,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_pTerrainIB,NULL);
m_pTerrainIB->Lock(0,0,(void**)&pIndexData,0);


for(unsigned x = 0;x < TERRAIN_X;++x)
{
	for(unsigned z = 0;z < TERRAIN_Z;++z)
	{
	  *pIndexData++ = x + z * (TERRAIN_X + 1);
	  *pIndexData++ = x + 1 + z * (TERRAIN_X + 1);
	  *pIndexData++ = x + 1 + (z + 1) * (TERRAIN_X + 1);

	  *pIndexData++ = x + z * (TERRAIN_X + 1);
	  *pIndexData++ = x + 1 + (z + 1) * (TERRAIN_X + 1);
	  *pIndexData++ = x + (z + 1) * (TERRAIN_X + 1);
	}
}
m_pTerrainIB->Unlock();
}


void Terrain::CreateTerrain(LPDIRECT3DDEVICE9& d3ddev)
{
	LoadHeighMap("heightmap.raw");
	LoadVertexBuffer(d3ddev);
	LoadIndexBuffer(d3ddev);
}


//CreateTerrain

/************************************************************************/
/* Name:		Draw													*/
/* Description:	draw terrain											*/
/************************************************************************/

void Terrain::Draw(LPDIRECT3DDEVICE9& d3ddev)
{

	d3ddev->SetFVF(CUSTOMFVF);

	D3DMATERIAL9 material;    // create the material struct
	ZeroMemory(&material, sizeof(D3DMATERIAL9));    // clear out the struct for use
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to yellow
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to yellow
	d3ddev->SetMaterial(&material);    // set the globably-used material to &material
	d3ddev->SetStreamSource(0,m_pTerrainVB,0,sizeof(CUSTOMVERTEX));
	d3ddev->SetIndices(m_pTerrainIB);
	d3ddev->SetTexture(0, texture);
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,m_dwTerrainVertices,0,m_dwTerrainPrimitives);
}//Draw

float Terrain::Set_height(float x,float z){
	if(x<0 || x>256 || z<0 || z>256) return 0;

	float height;
	float A = HeightMap[(int)x][(int)z];
	float B = HeightMap[(int)x][(int)z+1];
	float C = HeightMap[(int)x+1][(int)z];
	float D = HeightMap[(int)x+1][(int)z+1];
	float dx = x - (int)x;
	float dz = z - (int)z;

	if(dz < 1.0f - dx) // upper triangle ABC
	{
		float uy = B - A; // A->B
		
		float vy = C - A; // A->C
		height = A + uy*dx + vy*dz;
	}
	else // lower triangle DCB
	{

		float uy = C - D; // D->C
		float vy = B - D; // D->B
		height = D + (uy*(1.0f - dx))+(vy*(1.0f - dz));
	} return height/3;
}



