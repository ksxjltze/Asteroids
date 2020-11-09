#include "constants.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"

Bullet Asteroids_Collision_CheckCollision_Enemy_Bullet(Enemy arr_enemy[], int enemy_count, Bullet bullet);
void Asteroids_Collision_CheckCollision_Enemy_Player(Enemy arr_enemy[], int enemy_count, Player* player);