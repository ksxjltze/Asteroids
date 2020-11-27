#pragma once

typedef struct States
{
	int id;
	const char* name;
	void(*action)(void* context);
} State;