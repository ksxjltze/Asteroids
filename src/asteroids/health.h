#pragma once
typedef struct Health {
	float current;
	float max;
}Health;

void Asteroids_Health_UI_Draw(Health hp);
void Asteroids_Health_UI_Init();