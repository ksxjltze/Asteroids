#pragma once
#include <stdio.h>

FILE* Asteroids_Open_File(const char* path, const char* mode);
void Asteroids_Close_File(FILE* file);