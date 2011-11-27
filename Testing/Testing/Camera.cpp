#include "Globalincludes.h"
#include "Camera.h"
#include "Entity.h"
#include "math.h"

Camera::Camera(){
C_Position = D3DXVECTOR3(-50.0f,50.0f,-50.0f);
C_LookAtPos = D3DXVECTOR3(50.0f,0.0f,50.0f);
C_UpVect = D3DXVECTOR3(0.0f,1.0f,0.0f);
SensitivityX=0.5f;
SensitivityY=0.5f;
movingX=0;
movingY=0;
attached = false;
}
void Camera::Update(LPDIRECT3DDEVICE9& d3ddev){
	if(attached) Attach_rotate();
	else Rotate();
	D3DXMATRIX	m_matView;
	D3DXMatrixLookAtLH(&m_matView,&C_Position,&C_LookAtPos,&C_UpVect);
	d3ddev->SetTransform(D3DTS_VIEW,&m_matView);

}

void Camera::Attach(Entity* entity_){
	attached = true;
	attached_object = entity;
	entity=entity_;
}

void Camera::Move(D3DXVECTOR3 Direction){
	
	D3DXVec3Normalize(&Direction,&Direction);
	  C_Position += Direction * 0.5f;
	  C_LookAtPos += Direction * 0.5f;
	
}

void Camera::Attach_rotate(){
	C_Position = entity->Position;
	C_Position.x -= 10;
	C_Position.y += 1;	
	C_LookAtPos = entity->Position;
	C_LookAtPos.y += 1;
	
	if(movingX > 1.5) movingX=1.5;
	if(movingX <-1.5) movingX=-1.5;
	D3DXVECTOR3 vVector = C_Position - C_LookAtPos;
	movingY =-movingY;
	movingX =-movingX;
	C_Position.y = (float)(C_LookAtPos.y + cos(movingX)*vVector.y - sin(movingX)*vVector.x);
	C_Position.z = (float)(C_LookAtPos.z + (sin(movingY)*vVector.x + cos(movingY)*vVector.z)*cos(movingX));
	C_Position.x = (float)(C_LookAtPos.x + (cos(movingY)*vVector.x - sin(movingY)*vVector.z)*cos(movingX));
	movingY =-movingY;
	movingX =-movingX;
}

void Camera::Rotate(){
	D3DXVECTOR3 Direction,RotAxis;
	D3DXMATRIX matRotAxis,matRotY;
				
	D3DXVec3Normalize(&Direction,&(C_LookAtPos - C_Position));
	D3DXVec3Cross(&RotAxis,&Direction,&C_UpVect);
	D3DXVec3Normalize(&RotAxis,&RotAxis);

	D3DXMatrixRotationAxis(&matRotAxis,&RotAxis,SensitivityX*movingX);
	D3DXMatrixRotationY(&matRotY,SensitivityY*movingY);

	D3DXVec3TransformCoord(&Direction,&Direction,&(matRotAxis * matRotY));
	D3DXVec3TransformCoord(&C_UpVect,&C_UpVect,&(matRotAxis * matRotY));
	C_LookAtPos = Direction + C_Position;
	movingX=0;
	movingY=0;
}