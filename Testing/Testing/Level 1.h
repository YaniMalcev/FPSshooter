#ifndef __LEVEL1_H__
#define __LEVEL1_H__
#include "Levels.h"

struct Level1 : GameLevel{
	 void Init();
     GameLevel* OnUpdate();
     void Render();
	 void HandleKeyboard();
	 void HandleMouse(RAWINPUT InputData);
     void OnLeave();
};

#endif