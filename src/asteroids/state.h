//---------------------------------------------------------
// file:	state.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	State struct header file.
//			Provides definition of the state struct for state machines (i.e. Boss AI)
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once

typedef struct States
{
	int id;
	const char* name;
	void(*action)(void* context);
} State;