#ifndef __GAME_H__
#define __GAME_H__
#include "Globalincludes.h"
#include "Camera.h"
#include "Terrain.h"
#include "LevelManager.h"
#include "level 1.h"
class Game{
	LPDIRECT3DDEVICE9 d3ddev;
	HWND hWnd;
	LevelManager* levelmanager; 
	Camera* camera;
	Terrain* terrain;
	POINT MousePos;
	void Init_Window(HINSTANCE hInstance);
	void Init_D3D();
	void init_input(HWND hWnd);
	void HandleKeyboard();
	void HandleMouse(RAWINPUT InputData);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void update();
	void render();

	//FPS variables
	
const int FPS;
const DWORD TIME_PER_FRAME;
const float FRACTION_TIME_PER_FRAME;

public:
	Game();
	void Init(HINSTANCE hInstance);
	void Run();
	void End();
};

#endif