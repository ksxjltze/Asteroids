#include "constants.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"

struct Bullet Asteroids_Collision_CheckCollision_Enemy_Bullet(Enemy arr_enemy[], int enemy_count, struct Bullet bullet);
void Asteroids_Collision_CheckCollision_Enemy_Player(Enemy arr_enemy[], int enemy_count, struct Player* player);
int Asteroids_Collision_CheckCollision_Circle_AABB(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_AABB, CP_Vector pos2);