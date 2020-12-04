#pragma once

#include "../../CProcessing/inc/cprocessing.h"

void Camera_Initialize();
void Camera_Update(const float dt);
void Camera_Exit();
CP_Matrix Camera_GetCameraTransform();

float Camera_GetX();
float Camera_GetY();
void Camera_SetX(const float x);
void Camera_SetY(const float y);
void Camera_SetRotation(const float rotation);
float Camera_GetRotation();

void Camera_Shake(float strength);
void Camera_ShakeUpdate(const float dt);