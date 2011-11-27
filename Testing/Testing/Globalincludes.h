#ifndef __GLOBALINCLUDES_H__
#define __GLOBALINCLUDES_H__

#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include<iostream>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
using namespace std;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 1000
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
struct CUSTOMVERTEX {FLOAT X, Y, Z; D3DVECTOR NORMAL;FLOAT U,V;};


#endif