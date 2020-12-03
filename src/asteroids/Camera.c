#include "Camera.h"

CP_Vector Camera_position;
CP_Vector Camera_position_inverse;
float Camera_rotation = 0.0f;

float Camera_shake_strength = 0;
float Camera_shake_dampening = 40.0f;
CP_Vector Camera_shake_offset;

void Camera_Initialize()
{
	Camera_position = (CP_Vector){ 0.0f, 0.0f };
	Camera_position_inverse = (CP_Vector){ 0.0f, 0.0f };
	Camera_shake_offset = (CP_Vector){ 0.0f, 0.0f };
}

void Camera_Update(const float dt)
{
	Camera_ShakeUpdate(dt);
}

void Camera_Exit()
{
}

CP_Matrix Camera_GetCameraTransform()
{
	//CP_Matrix transform = CP_Matrix_Rotate(Camera_rotation);
	return CP_Matrix_Translate(CP_Vector_Add(Camera_position_inverse, Camera_shake_offset));
}

float Camera_GetX()
{
	return Camera_position.x;
}

float Camera_GetY()
{
	return Camera_position.y;
}

void Camera_SetX(const float x)
{
	Camera_position.x = x;
	Camera_position_inverse.x = -x;
}

void Camera_SetY(const float y)
{
	Camera_position.y = y;
	Camera_position_inverse.y = -y;
}

void Camera_SetRotation(const float rotation)
{
	Camera_rotation = rotation;
}

float Camera_GetRotation()
{
	return Camera_rotation;
}

void Camera_Shake(float strength)
{
	Camera_shake_strength = strength;
}

void Camera_ShakeUpdate(const float dt)
{
	// apply dampen to strength
	if (Camera_shake_strength > 0.1f) {
		Camera_shake_strength = CP_Math_LerpFloat(Camera_shake_strength, 0.0f, Camera_shake_dampening*dt);
	}
	else {
		Camera_shake_strength = 0.0f;
	}
	CP_Vector direction = (CP_Vector){
		CP_Random_RangeFloat(-1.0f,1.0f),
		CP_Random_RangeFloat(-1.0f,1.0f)
	};
	direction = CP_Vector_Normalize(direction);
	Camera_shake_offset.x = direction.x * Camera_shake_strength;
	Camera_shake_offset.y = direction.y * Camera_shake_strength;
}
