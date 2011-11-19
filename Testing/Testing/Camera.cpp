#include "Globalincludes.h"
#include "Camera.h"



Camera::Camera(){
C_Postion = D3DXVECTOR3(-50.0f,50.0f,-50.0f);
C_LookAtPos = D3DXVECTOR3(50.0f,0.0f,50.0f);
C_UpVect = D3DXVECTOR3(0.0f,1.0f,0.0f);
SensitivityX=0.5f;
SensitivityY=0.5f;
movingX=0;
movingY=0;
}
void Camera::Update(LPDIRECT3DDEVICE9 d3ddev){
	Rotate();
	D3DXMATRIX	m_matView;
	D3DXMatrixLookAtLH(&m_matView,&C_Postion,&C_LookAtPos,&C_UpVect);
	d3ddev->SetTransform(D3DTS_VIEW,&m_matView);
}
void Camera::Move(D3DXVECTOR3 Direction){
	

	D3DXVec3Normalize(&Direction,&Direction);
	  C_Postion += Direction * 0.5f;
	  C_LookAtPos += Direction * 0.5f;
	
}
void Camera::Rotate(){
	D3DXVECTOR3 Direction,RotAxis;
	D3DXMATRIX matRotAxis,matRotY;
				
	D3DXVec3Normalize(&Direction,&(C_LookAtPos - C_Postion));
	D3DXVec3Cross(&RotAxis,&Direction,&C_UpVect);
	D3DXVec3Normalize(&RotAxis,&RotAxis);

	D3DXMatrixRotationAxis(&matRotAxis,&RotAxis,SensitivityX*movingX);
	D3DXMatrixRotationY(&matRotY,SensitivityY*movingY);

	D3DXVec3TransformCoord(&Direction,&Direction,&(matRotAxis * matRotY));
	D3DXVec3TransformCoord(&C_UpVect,&C_UpVect,&(matRotAxis * matRotY));
	C_LookAtPos = Direction + C_Postion;
	movingX=0;
	movingY=0;
}