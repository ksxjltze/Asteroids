#pragma once
#include "cprocessing.h"

extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;
extern const float SPLASH_DURATION;

extern const float MAX_VELOCITY; //pixels per second
extern const float SPEED;
extern const float ASTEROIDS_PLAYER_SLOWED_SPEED;

extern const int BULLET_SPEED;
extern const float FIRE_RATE; //bullets per minute
extern const float HURT_WINDOW; //seconds
extern const float BULLET_DAMAGE;
extern const float ASTEROIDS_ENEMY_BASE_MAX_HP;

extern const float ASTEROID_MAX_SPEED; //pixels per second
extern const float ASTEROID_MIN_SPEED; //pixels per second
extern const int ASTEROIDS_PLAYER_SIMPLE_SPEED;

extern const float ASTEROIDS_ENEMY_SIZE_MIN;
extern const float ASTEROIDS_ENEMY_SIZE_MAX;
extern const int ASTEROIDS_ENEMY_SPLIT_MAX_COUNT;
extern const int ASTEROIDS_ENEMY_SPLIT_MIN_NUMBER;
extern const int ASTEROIDS_ENEMY_SPLIT_MAX_NUMBER;
extern const int ASTEROIDS_ENEMY_BASE_DIAMETER;
extern const float ASTEROIDS_ENEMY_BASE_SPAWN_INTERVAL;

extern const float ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MIN;
extern const float ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MAX;

extern const float ASTEROIDS_ASTEROID_ENEMY_VELOCITY_OFFSET;
extern const float ASTEROIDS_ENEMY_SPAWN_OFFSET;

//Initial number of asteroids to spawn
extern const int ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MIN;
extern const int ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MAX;
extern const int ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MIN;
extern const int ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MAX;

extern const float ASTEROIDS_ASTEROID_ENEMY_BASE_DAMAGE;


//health bar
extern const float ASTEROIDS_UI_PLAYER_HEALTH_BAR_WIDTH;

extern const char* PLAYER_SPRITE_PATH;
extern const char* ASTEROIDS_HEART_SPRITE_PATH;

extern const float PLAYER_MAX_HP;
extern const float PLAYER_MAX_FUEL;
extern const float DRAIN_RATE;

extern const CP_KEY ASTEROIDS_PAUSE_KEY;

//ERROR
extern const char* ASTEROIDS_ERROR_STR_MISSING_SPRITE;
extern const float ASTEROIDS_DIFFICULTY_INTERVAL;