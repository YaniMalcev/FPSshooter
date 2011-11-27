
#include "Game.h"

Game game;
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    game.Init(hInstance);
	game.Run();
	game.End();
	
}