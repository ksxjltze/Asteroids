#include "constants.h"
extern const int WIN_WIDTH = 1280;
extern const int WIN_HEIGHT = 720;
extern const float SPLASH_DURATION = 3.0f;

extern const float MAX_VELOCITY = 10.0f; //pixels per second
extern const float SPEED = 200.0f;
extern const float ASTEROIDS_PLAYER_SLOWED_SPEED = 20.0f;

extern const int BULLET_SPEED = 1000;
extern const float FIRE_RATE = 600.0f; //bullets per minute
extern const float HURT_WINDOW = 0.1f; //seconds
extern const float BULLET_DAMAGE = 1;
extern const float ENEMY_HP = 3;

extern const float ASTEROID_MIN_SPEED = 50.0f;
extern const float ASTEROID_MAX_SPEED = 200.0f; //pixels per second
extern const int ASTEROIDS_PLAYER_SIMPLE_SPEED = 10;

extern const float ASTEROIDS_ENEMY_SIZE_MIN = 1.0f;
extern const float ASTEROIDS_ENEMY_SIZE_MAX = 5.0f;
extern const int ASTEROIDS_ENEMY_SPLIT_MAX_COUNT = 3;
extern const int ASTEROIDS_ENEMY_SPLIT_MIN_NUMBER = 2;
extern const int ASTEROIDS_ENEMY_SPLIT_MAX_NUMBER = 10;
extern const int ASTEROIDS_ENEMY_BASE_DIAMETER = 32;

extern const float ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MIN = -60.0f;
extern const float ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MAX = 60.0f;

extern const float ASTEROIDS_ASTEROID_ENEMY_VELOCITY_OFFSET = 300.0f;
extern const float SPAWN_OFFSET = 300.0f;

extern const int ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MIN = 5;
extern const int ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MAX = 15;
extern const int ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MIN = 2;
extern const int ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MAX = 3;

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