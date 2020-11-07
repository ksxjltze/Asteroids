#include "constants.h"
extern const int WIN_WIDTH = 1280;
extern const int WIN_HEIGHT = 720;
extern const float SPLASH_DURATION = 3.0f;

extern const float MAX_VELOCITY = 10.0f; //pixels per second
extern const int SPEED = 10;

extern const int BULLET_SPEED = 1000;
extern const float FIRE_RATE = 600.0f; //bullets per minute
extern const float HURT_WINDOW = 0.1f; //seconds
extern const float BULLET_DAMAGE = 1;
extern const float ENEMY_HP = 3;

extern const float ASTEROID_MIN_SPEED = 50.0f;
extern const float ASTEROID_MAX_SPEED = 200.0f; //pixels per second
extern const float ASTEROIDS_ASTEROID_ENEMY_VELOCITY_OFFSET = 300.0f;
extern const float SPAWN_OFFSET = 300.0f;

//health bar
extern const float BAR_WIDTH = 100;
extern const float BAR_HEIGHT = 10;
extern const float BAR_OFFSET_Y = 10;

extern const char* PLAYER_SPRITE_PATH = "./Assets/spaceship1.png";
extern const char* ASTEROIDS_HEART_SPRITE_PATH = "./Assets/heart.png";
extern const float PLAYER_MAX_HP = 3;

extern const float PLAYER_MAX_FUEL = 100.0f;
extern const float DRAIN_RATE = 5.0f;

extern const CP_KEY ASTEROIDS_PAUSE_KEY = KEY_ESCAPE;
extern const float ENEMY_SPAWN_TIME = 2.0f;

extern const char* ASTEROIDS_ERROR_STR_MISSING_SPRITE = "ERROR - Missing Sprite";