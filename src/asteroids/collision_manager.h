#include "constants.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"

Bullet Asteroids_Collision_CheckCollision_Enemy_Bullet(Enemy enemy_pool[], int enemy_count, Bullet bullet);
void Asteroids_Collision_CheckCollision_Enemy_Player(Enemy enemy_pool[], int enemy_count, Player* player);
void Asteroids_Collision_CheckCollision_Enemy_Enemy(Enemy enemy_pool[], int enemy_count, Enemy* enemy);