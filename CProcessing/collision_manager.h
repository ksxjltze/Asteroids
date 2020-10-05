#include "constants.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"

struct Bullet check_collision_enemy_bullet(struct Enemy arr_enemy[], int enemy_count, struct Bullet bullet);
void check_collision_enemy_player(struct Enemy arr_enemy[], int enemy_count, struct Player* player);
int check_collision_circle_aabb(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_AABB, CP_Vector pos2);