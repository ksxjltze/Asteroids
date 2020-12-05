#pragma once
#include "cprocessing.h"
//---------------------------------------------------------
// file:	constants.h
// author:	Lee Jia Keat

// contributors: Bryan Koh Yan Wei


// email:	l.jiakeat@digipen.edu
//			yanweibryan.koh@digipen.edu
//
// brief:	File holding constants for the game


// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------


/*				MISCALLENOUS CONSTANTS					*/
extern int WIN_WIDTH;
extern int WIN_HEIGHT;
extern const CP_KEY ASTEROIDS_PAUSE_KEY;
extern const float SPLASH_DURATION;
extern const float ASTEROIDS_INPUT_BACKSPACE_DELETE_SPEED;
extern const char* ASTEROIDS_ERROR_STR_MISSING_SPRITE;
extern const float HURT_WINDOW;			//seconds
extern const float PLAYER_HURT_WINDOW;



/*				PLAYER MOVEMENT CONSTANTS				*/
extern const float MAX_VELOCITY;		//pixels per second
extern const float ASTEROIDS_PLAYER_BASE_MOVE_SPEED;
extern const float ASTEROIDS_PLAYER_SLOWED_SPEED;




/*				VFX CONSTANTS							*/	
extern const float ASTEROIDS_SPRITE_EXPLOSION_DIMENSIONS_SCALE_FACTOR;
extern const float ASTEROIDS_OBSTACLES_DOT_PARTICLE_LIFESPAN;




/*				WEAPON CONSTANTS						*/
extern const float ASTEROIDS_WEAPON_RAILGUN_PROJECTILE_SPEED;
extern const float ASTEROIDS_WEAPON_RAILGUN_FIRE_RATE; //bullets per minute
extern const float ASTEROIDS_WEAPON_RAILGUN_DAMAGE;
extern const int ASTEROIDS_WEAPON_SWARM_BULLET_MAX_ATTACK_COUNT;





/*				MAIN MENU CONSTANTS						*/	
extern const float ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_OFFSET;
extern const float ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_SPEED;
extern const int ASTEROIDS_PLAYER_SIMPLE_SPEED;




/*				ENEMY CONSTANTS							*/	
extern const float ASTEROID_MAX_SPEED; //pixels per second
extern const float ASTEROID_MIN_SPEED; //pixels per second
extern const float ASTEROIDS_ENEMY_SIZE_MIN;				 
extern const float ASTEROIDS_ENEMY_SIZE_MAX;
extern const int ASTEROIDS_ENEMY_SPLIT_MAX_COUNT;
extern const int ASTEROIDS_ENEMY_SPLIT_MIN_NUMBER;
extern const int ASTEROIDS_ENEMY_SPLIT_MAX_NUMBER;
extern const float ASTEROIDS_ENEMY_SPLIT_SIZE_SCALE_FACTOR;
extern const int ASTEROIDS_ENEMY_BASE_DIAMETER;
extern const float ASTEROIDS_ENEMY_BASE_SPAWN_INTERVAL;
extern const float ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MIN;
extern const float ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MAX;
extern const float ASTEROIDS_ASTEROID_ENEMY_VELOCITY_OFFSET;
extern const float ASTEROIDS_ENEMY_SPAWN_OFFSET;
extern const int ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MIN;
extern const int ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MAX;
extern const int ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MIN;
extern const int ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MAX;
extern const float ASTEROIDS_ASTEROID_ENEMY_BASE_DAMAGE;
extern const float ASTEROIDS_ENEMY_BASE_MAX_HP;




/*				FILE PATH CONSTANTS							*/
extern const char* ASTEROIDS_PLAYER_SPRITE_PATH_DEFAULT;
extern const char* ASTEROIDS_PLAYER_SPRITE_PATH_LEGACY;
extern const char* ASTEROIDS_PLAYER_SPRITE_PATH_PROTOTYPE;
extern const char* ASTEROIDS_HEART_SPRITE_PATH;






/*				UI RELATED CONSTANTS						*/	
extern const float ASTEROIDS_UI_PLAYER_HEALTH_BAR_WIDTH;
extern const float ASTEROIDS_UI_PLAYER_FUEL_METER_BAR_WIDTH;
extern const float ASTEROIDS_UI_PLAYER_FUEL_METER_BAR_HEIGHT;
extern const float PLAYER_MAX_HP;
extern const float PLAYER_MAX_FUEL;
extern const float DRAIN_RATE;
extern const float ASTEROIDS_PLAYER_FUEL_REFUEL_AMOUNT;
extern const float ASTEROIDS_PLAYER_FUEL_DRAIN_THRESHOLD;
extern const float ASTEROIDS_PLAYER_SPRITE_WIDTH;
extern const float ASTEROIDS_PLAYER_SPRITE_HEIGHT;





/*				UPGRADES CONSTANTS							*/	
extern const float ASTEROIDS_UPGRADES_FUEL_UPGRADE_AMOUNT;
extern const int ASTEROIDS_UPGRADES_FUEL_UPGRADE_COST;
extern const float ASTEROIDS_UPGRADES_MAX_HEALTH_UPGRADE_AMOUNT;
extern const int ASTEROIDS_UPGRADES_MAX_HEALTH_UPGRADE_COST;
extern const float ASTEROIDS_UPGRADES_BULLET_DAMAGE_UPGRADE_AMOUNT;
extern const int ASTEROIDS_UPGRADES_BULLET_DAMAGE_UPGRADE_COST;
extern const float ASTEROIDS_UPGRADES_MOVEMENT_SPEED_UPGRADE_AMOUNT;
extern const int ASTEROIDS_UPGRADES_MOVEMENT_SPEED_UPGRADE_COST;
extern const float ASTEROIDS_UPGRADES_FIRE_RATE_UPGRADE_AMOUNT;
extern const int ASTEROIDS_UPGRADES_FIRE_RATE_UPGRADE_COST;
extern const float ASTEROIDS_UPGRADES_PROJECTILE_SPEED_UPGRADE_AMOUNT;
extern const int ASTEROIDS_UPGRADES_PROJECTILE_SPEED_UPGRADE_COST;
extern const int ASTEROIDS_UPGRADES_PIERCING_PROJECTILES_UPGRADE_COST;
extern const float ASTEROIDS_UPGRADES_MENU_ITEM_HORIZONTAL_MARGIN; 
extern const float ASTEROIDS_UPGRADES_MENU_ITEM_VERTICAL_MARGIN;



extern const int ASTEROIDS_UPGRADES_PIERCING_PROJECTILES_UPGRADE_COST;
extern const int ASTEROIDS_UPGRADES_MULTISHOT_UPGRADE_COST;
extern const float ASTEROIDS_UPGRADES_MULTISHOT_ANGLE;
extern const int ASTEROIDS_UPGRADES_HOMING_PROJECTILES_UPGRADE_COST;
extern const int ASTEROIDS_UPGRADES_SWARM_PROJECTILES_UPGRADE_COST;

/*				CREDITS CONSTANTS							*/
extern const int ASTEROIDS_CURRENCY_STARTING_BALANCE;
extern const int ASTEROIDS_CURRENCY_EARNING_BALANCE_BASE;
extern const int ASTEROIDS_CURRENCY_EARNING_BALANCE_MAX;
extern const int ASTEROIDS_ENEMY_CURRENCY_DROP_AMOUNT;




/*				DIFFICULTY CONSTANTS						*/	
extern const float ASTEROIDS_DIFFICULTY_INTERVAL;
extern const int ASTEROIDS_DIFFICULTY_CAP;




/*				POWERUP CONSTANTS							*/			
extern const float ASTEROIDS_POWERUP_LIFESPAN_DURATION;
extern const float ASTEROIDS_POWERUP_INVUNERABILITY_DURATION;
extern const float ASTEROIDS_POWERUP_HP_RECOVERY_VALUE;
extern const float ASTEROIDS_POWERUP_INCREASE_FIRERATE_VALUE;
extern const float ASTEROIDS_POWERUP_BULLET_SPLIT_ANGLE;




/*				OBSTACLE CONSTANTS							*/
extern const float ASTEROIDS_OBSTACLE_BACKHOLE_DAMAGE;
extern const float ASTEROIDS_OBSTACLE_GAMMARAY_DAMAGE;
extern const float ASTEROIDS_OBSTACLE_SPAWN_INTERVAL;
extern const float ASTEROIDS_OBSTACLE_WARNING_INTERVAL;
extern const float ASTEROIDS_OBSTACLE_BLACKHOLE_SPEED;
extern const float ASTEROIDS_OBSTACLE_GAMMARAY_SPEED;
extern const float ASTEROIDS_OBSTACLE_LIFESPAN;
extern const float ASTEROIDS_OBSTACLE_BLACKHOLE_WIDTH;
extern const float ASTEROIDS_OBSTACLE_GAMARAY_HEIGHT;



/*				SUPER ASTEROIDS CONSTANTS					*/
extern const float ASTEROIDS_ENEMY_BIGBOY_BASE_HP;
extern const float ASTEROIDS_ENEMY_BIGBOY_SPAWN_INTERVAL;
extern const float ASTEROIDS_ENEMY_BIGBOY_SPEED;




/*				FINAL_BOSS CONSTANTS						*/
extern const float ASTEROIDS_FINAL_BOSS_SLEEP_DMG_REDUCTION;
extern const float ASTEROIDS_FINAL_BOSS_SUMMON_ANIMATION_TIMER;
extern const float ASTEROIDS_FINAL_BOSS_SUMMON_ANIMATION_COUNT;
extern const float ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE;
extern const int ASTEROIDS_FINAL_BOSS_ATTACK_STATE_PROJECTILE_NUM;
extern const int ASTEROIDS_FINAL_BOSS_BULLET_HELL_STATE_PROJECTILE_NUM;
extern const float ASTEROIDS_FINAL_BOSS_MAX_HP;
extern const float ASTEROIDS_FINAL_BOSS_PROJECTILE_SPEED;
extern const float ASTEROIDS_FINAL_BOSS_MOVEMENT_SPEED;
extern const float ASTEROIDS_FINAL_BOSS_DIAMETER;
extern const int ASTEROIDS_FINAL_BOSS_SUMMON_CRITERIA;
extern const float ASTEROIDS_FINAL_BOSS_FIRE_RATE;
extern const float ASTEROIDS_FINAL_BOSS_DODGE_STATE_FIRE_RATE;
extern const float ASTEROIDS_FINAL_BOSS_BULLETHELL_STATE_FIRE_RATE;
extern const float ASTEROIDS_FINAL_BOSS_IDLE_STATE_FIRE_RATE;
extern const float ASTEROIDS_FINAL_BOSS_STATE_CHANGE_RATE;
extern const float ASTEROIDS_FINAL_BOSS_ENRAGED_STATE_BASE_SPEED;
extern const float ASTEROIDS_FINAL_BOSS_DODGE_STATE_BASE_SPEED;
extern const float ASTEROIDS_FINAL_BOSS_ENRAGED_DMG_AMP;