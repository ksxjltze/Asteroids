#pragma once

typedef struct States
{
	int id;
	const char* name;
	void(*action);
} State;

void Asteroids_State_Init();
void Asteroids_State_Set();
void Asteroids_State_Update();
void Asteroids_State_CheckConditions();
void Asteroids_State_Enter();
void Asteroids_State_Exit();