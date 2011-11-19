#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera{

	float SensitivityX;
	float SensitivityY;

public:
	float movingX,movingY;
	D3DXVECTOR3 C_Postion,
				C_LookAtPos,
				C_UpVect; //the camera "up" direction
	
	
			Camera();
			void Move(D3DXVECTOR3 Direction);
			void Rotate();
			void Update(LPDIRECT3DDEVICE9 d3ddev);
};

#endif