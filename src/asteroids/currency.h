#pragma once
#include <stdbool.h>

void Asteroids_Currency_Init(void);
void Asteroids_Currency_Add(int amount);
int Asteroids_Currency_Get_Balance();
bool Asteroids_Currency_Deduct_Balance(int amount);
bool Asteroids_Currency_Get_From_File();
void Asteroids_Currency_Write_To_File();