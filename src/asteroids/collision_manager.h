#include "constants.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "collider_aabb.h"
#include "collider_circle.h"
#include <stdbool.h>

Bullet Asteroids_Collision_CheckCollision_Enemy_Bullet(Enemy enemy_pool[], int enemy_count, Bullet bullet);
void Asteroids_Collision_CheckCollision_Enemy_Player(Enemy enemy_pool[], int enemy_count, Player* player);
void Asteroids_Collision_CheckCollision_Enemy_Enemy(Enemy enemy_pool[], int enemy_count, Enemy* enemy, Player player);
bool Asteroids_Collision_CheckCollision_AABB_Circle(struct Collider_AABB aabb, CP_Vector aabb_pos, struct Collider_Circle circle, CP_Vector circle_pos);