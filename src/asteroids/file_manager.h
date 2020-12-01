//---------------------------------------------------------
// file:	file_manager.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
// brief:	File Manager header file
//			Provides an interface for Opening and Closing files.
//			Handles errors for file manipulation and prints
//			them (to some extent) to the std output stream.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <stdio.h>

FILE* Asteroids_Open_File(const char* path, const char* mode);
void Asteroids_Close_File(FILE* file);