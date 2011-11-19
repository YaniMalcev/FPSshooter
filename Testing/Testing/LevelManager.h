#ifndef __LEVELMANAGER_H__
#define __LEVELMANAGER_H__
#include "Globalincludes.h"
#include "Levels.h"
struct LevelManager
{
    
    static GameLevel* currentLevel;
    bool Update();
    void Render();
	void HandleKeyboard();
	void HandleMouse(RAWINPUT InputData);
    void ChangeLevel(GameLevel* Level);
};

#endif