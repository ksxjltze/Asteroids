#include "constants.h"
//---------------------------------------------------------
// file:	constants.c
// author:	Lee Jia Keat

// contributors: Bryan Koh Yan Wei

// email:	l.jiakeat@digipen.edu
//			yanweibryan.koh@digipen.edu
//
// brief:	File holding constants for the game so that it does not look like magic nums
//			


// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------


/*				MISCALLENOUS CONSTANTS					*/
const float SPLASH_DURATION = 3.0f;
const CP_KEY ASTEROIDS_PAUSE_KEY = KEY_ESCAPE;
const char* ASTEROIDS_ERROR_STR_MISSING_SPRITE = "ERROR - Missing Sprite";
const float HURT_WINDOW = 0.01f; //seconds
const float PLAYER_HURT_WINDOW = 1.0f; //seconds
const float ASTEROIDS_INPUT_BACKSPACE_DELETE_SPEED = 0.05f;
const int DEFAULT_WIN_WIDTH = 1280;
const int DEFAULT_WIN_HEIGHT = 720;




/*				PLAYER MOVEMENT CONSTANTS				*/
const float MAX_VELOCITY = 10.0f; //pixels per second
const float ASTEROIDS_PLAYER_BASE_MOVE_SPEED = 300.0f;
const float ASTEROIDS_PLAYER_SLOWED_SPEED = 50.0f;
const int ASTEROIDS_PLAYER_SIMPLE_SPEED = 400;




/*				VFX CONSTANTS								*/
const float ASTEROIDS_OBSTACLES_DOT_PARTICLE_LIFESPAN = 1.5f;
const float ASTEROIDS_SPRITE_EXPLOSION_DIMENSIONS_SCALE_FACTOR = 0.3f;




/*				WEAPON CONSTANTS						*/
const float ASTEROIDS_WEAPON_RAILGUN_PROJECTILE_SPEED = 400;
const float ASTEROIDS_WEAPON_RAILGUN_FIRE_RATE = 200.0f; //bullets per minute
const float ASTEROIDS_WEAPON_RAILGUN_DAMAGE = 1;
const int ASTEROIDS_WEAPON_SWARM_BULLET_MAX_ATTACK_COUNT = 50;




/*				ENEMY CONSTANTS							*/
const float ASTEROID_MIN_SPEED = 50.0f;
const float ASTEROID_MAX_SPEED = 200.0f; //pixels per second
const float ASTEROIDS_ENEMY_BASE_MAX_HP = 6.0f;
const float ASTEROIDS_ENEMY_BASE_SPAWN_INTERVAL = 2.0f;
const float ASTEROIDS_ENEMY_SIZE_MIN = 1.0f;
const float ASTEROIDS_ENEMY_SIZE_MAX = 8.0f;
const int ASTEROIDS_ENEMY_BASE_DIAMETER = 32;
const int ASTEROIDS_ENEMY_SPLIT_MAX_COUNT = 3;
const int ASTEROIDS_ENEMY_SPLIT_MIN_NUMBER = 2;
const int ASTEROIDS_ENEMY_SPLIT_MAX_NUMBER = 8;
const float ASTEROIDS_ENEMY_SPLIT_SIZE_SCALE_FACTOR = 2.0f;
const float ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MIN = -60.0f;
const float ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MAX = 60.0f;
const float ASTEROIDS_ASTEROID_ENEMY_VELOCITY_OFFSET = 300.0f;
const float ASTEROIDS_ENEMY_SPAWN_OFFSET = 300.0f;
const int ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MIN = 5;
const int ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MAX = 15;
const int ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MIN = 2;
const int ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MAX = 3;
const float ASTEROIDS_ASTEROID_ENEMY_BASE_DAMAGE = 2.0f;






/*				FILE PATH CONSTANTS							*/
const char* ASTEROIDS_PLAYER_SPRITE_PATH_DEFAULT = "./Assets/Spaceship2.png";
const char* ASTEROIDS_PLAYER_SPRITE_PATH_LEGACY = "./Assets/spaceship1.png";
const char* ASTEROIDS_PLAYER_SPRITE_PATH_PROTOTYPE = "./Assets/ship_temp.png";
const char* ASTEROIDS_HEART_SPRITE_PATH = "./Assets/heart.png";



/*				UI RELATED CONSTANTS						*/
const float ASTEROIDS_UI_PLAYER_HEALTH_BAR_WIDTH = 300.0f;
const float ASTEROIDS_UI_PLAYER_FUEL_METER_BAR_WIDTH = 30.0f;
const float ASTEROIDS_UI_PLAYER_FUEL_METER_BAR_HEIGHT = 300.0f;
const float PLAYER_MAX_HP = 20.0f;
const float PLAYER_MAX_FUEL = 50.0f;
const float DRAIN_RATE = 4.0f;
const float ASTEROIDS_PLAYER_FUEL_REFUEL_AMOUNT = 30.0f;
const float ASTEROIDS_PLAYER_FUEL_DRAIN_THRESHOLD = 100.0f;
const float ASTEROIDS_PLAYER_SPRITE_WIDTH = 36.0f;
const float ASTEROIDS_PLAYER_SPRITE_HEIGHT = 54.0f;




/*				UPGRADES CONSTANTS							*/
const float ASTEROIDS_UPGRADES_MENU_ITEM_HORIZONTAL_MARGIN = 0.2f;
const float ASTEROIDS_UPGRADES_MENU_ITEM_VERTICAL_MARGIN = 0.25f;
const float ASTEROIDS_UPGRADES_FUEL_UPGRADE_AMOUNT = 50.0f;
const int ASTEROIDS_UPGRADES_FUEL_UPGRADE_COST = 1000;
const float ASTEROIDS_UPGRADES_MAX_HEALTH_UPGRADE_AMOUNT = 10.0f;
const int ASTEROIDS_UPGRADES_MAX_HEALTH_UPGRADE_COST = 1000;
const float ASTEROIDS_UPGRADES_BULLET_DAMAGE_UPGRADE_AMOUNT = 0.1f;
const int ASTEROIDS_UPGRADES_BULLET_DAMAGE_UPGRADE_COST = 2000;
const float ASTEROIDS_UPGRADES_MOVEMENT_SPEED_UPGRADE_AMOUNT = 10.0f;
const int ASTEROIDS_UPGRADES_MOVEMENT_SPEED_UPGRADE_COST = 1000;
const float ASTEROIDS_UPGRADES_FIRE_RATE_UPGRADE_AMOUNT = 50.0f;
const int ASTEROIDS_UPGRADES_FIRE_RATE_UPGRADE_COST = 3000;
const float ASTEROIDS_UPGRADES_PROJECTILE_SPEED_UPGRADE_AMOUNT = 50.0f;
const int ASTEROIDS_UPGRADES_PROJECTILE_SPEED_UPGRADE_COST = 4000;
const int ASTEROIDS_UPGRADES_PIERCING_PROJECTILES_UPGRADE_COST = 20000;
const int ASTEROIDS_UPGRADES_MULTISHOT_UPGRADE_COST = 60000;
const float ASTEROIDS_UPGRADES_MULTISHOT_ANGLE = 10.0f;
const int ASTEROIDS_UPGRADES_HOMING_PROJECTILES_UPGRADE_COST = 120000;
const int ASTEROIDS_UPGRADES_SWARM_PROJECTILES_UPGRADE_COST = 240000;






/*				CREDITS CONSTANTS							*/
const int ASTEROIDS_CURRENCY_STARTING_BALANCE = 10000;
const int ASTEROIDS_ENEMY_CURRENCY_DROP_AMOUNT = 1;
const int ASTEROIDS_CURRENCY_EARNING_BALANCE_BASE = 1;
const int ASTEROIDS_CURRENCY_EARNING_BALANCE_MAX = 5;


/*				DIFFICULTY CONSTANTS						*/
const float ASTEROIDS_DIFFICULTY_INTERVAL = 5.0f;// ChAng
const int ASTEROIDS_DIFFICULTY_CAP = 10;




/*				POWERUP CONSTANTS							*/
const float ASTEROIDS_POWERUP_LIFESPAN_DURATION = 10.0f;
const float ASTEROIDS_POWERUP_INVUNERABILITY_DURATION = 5.0f;
const float ASTEROIDS_POWERUP_HP_RECOVERY_VALUE = 5.0f;
const float ASTEROIDS_POWERUP_INCREASE_FIRERATE_VALUE = 2.0f;
const float ASTEROIDS_POWERUP_BULLET_SPLIT_ANGLE = 15.0f;

const float ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_OFFSET = 50.0f;
const float ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_SPEED = 15.0f;



/*				OBSTACLE CONSTANTS							*/
const float ASTEROIDS_OBSTACLE_BACKHOLE_DAMAGE = 2.0f;
const float ASTEROIDS_OBSTACLE_GAMMARAY_DAMAGE = 50.0f;
const float ASTEROIDS_OBSTACLE_SPAWN_INTERVAL = 10.0f;
const float ASTEROIDS_OBSTACLE_WARNING_INTERVAL = 7.0f;
const float ASTEROIDS_OBSTACLE_BLACKHOLE_SPEED = 1000.0f;
const float ASTEROIDS_OBSTACLE_GAMMARAY_SPEED = 3500.0f;
const float ASTEROIDS_OBSTACLE_BLACKHOLE_WIDTH  = 100.0f;
const float ASTEROIDS_OBSTACLE_GAMARAY_HEIGHT = 20.0f;



/*				SUPER ASTEROIDS CONSTANTS					*/
const float ASTEROIDS_ENEMY_BIGBOY_BASE_HP = 150.0f;
const float ASTEROIDS_ENEMY_BIGBOY_SPAWN_INTERVAL = 40.0f;
const float ASTEROIDS_ENEMY_BIGBOY_SPEED = 60.0f;



/*				FINAL_BOSS CONSTANTS						*/
const float ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE = 15.0f;
const int ASTEROIDS_FINAL_BOSS_ATTACK_STATE_PROJECTILE_NUM = 5;
const int ASTEROIDS_FINAL_BOSS_BULLET_HELL_STATE_PROJECTILE_NUM = 10;
const float ASTEROIDS_FINAL_BOSS_MAX_HP = 1400.0f;
const float ASTEROIDS_FINAL_BOSS_PROJECTILE_SPEED = 300.0f;
const float ASTEROIDS_FINAL_BOSS_PROJECTILE_SPEED_DIFFICULTY_SCALAR = 150.0f;
const float ASTEROIDS_FINAL_BOSS_MOVEMENT_SPEED = 10.0f;
const float ASTEROIDS_FINAL_BOSS_DIAMETER = 20.0f;
const int ASTEROIDS_FINAL_BOSS_SUMMON_CRITERIA = 2020;
const float ASTEROIDS_FINAL_BOSS_FIRE_RATE = 1.5f;
const float ASTEROIDS_FINAL_BOSS_FIRE_RATE_DIFFICULTY_SCALAR = 0.2f;
const float ASTEROIDS_FINAL_BOSS_DODGE_STATE_FIRE_RATE = 5.0f;
const float ASTEROIDS_FINAL_BOSS_BULLETHELL_STATE_FIRE_RATE = 0.5f;
const float ASTEROIDS_FINAL_BOSS_STATE_CHANGE_RATE = 10.0f;
const float ASTEROIDS_FINAL_BOSS_ENRAGED_STATE_BASE_SPEED = 350.0f;
const float ASTEROIDS_FINAL_BOSS_DODGE_STATE_BASE_SPEED = 500.0f;
const float ASTEROIDS_FINAL_BOSS_ENRAGED_DMG_AMP = 2.0f;
const float ASTEROIDS_FINAL_BOSS_SLEEP_DMG_REDUCTION = 0.5f;
const float ASTEROIDS_FINAL_BOSS_SUMMON_ANIMATION_TIMER = 1.0f;
const float ASTEROIDS_FINAL_BOSS_SUMMON_ANIMATION_COUNT = 3.0f;
const float ASTEROIDS_FINAL_BOSS_ENRAGED_STATE_PROJECTILE_SPEED = 800.0f;