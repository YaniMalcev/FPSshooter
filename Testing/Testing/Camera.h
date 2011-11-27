#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "Entity.h"
class Camera{

	float SensitivityX;
	float SensitivityY;

public:
	float movingX,movingY;
	bool attached;
	Entity* entity;
	Entity* attached_object;
	D3DXVECTOR3 C_Position,
				C_LookAtPos,
				C_UpVect; //the camera "up" direction
	
	
			Camera();
			void Attach(Entity* entity);
			void Attach_rotate();
			void Move(D3DXVECTOR3 Direction);
			void Rotate();
			void Update(LPDIRECT3DDEVICE9& d3ddev);
};

#endif