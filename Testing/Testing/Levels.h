#ifndef __LEVELS_H__
#define __LEVELS_H__
#include "Globalincludes.h"
struct GameLevel{
	virtual void Init() =0;
    virtual GameLevel* OnUpdate() =0;
    virtual void Render() =0;
	virtual void HandleKeyboard() =0;
	virtual void HandleMouse(RAWINPUT InputData) =0;
    virtual void OnLeave() =0;
};

#endif