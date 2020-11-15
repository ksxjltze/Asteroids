#include "enemy.h"
#include "particle.h"
#include "powerups.h"
#include "health.h"
#include "collider_circle.h"
#include "status.h"
#include "constants.h"
#include "utility.h"
#include "score.h"
#include "collision_manager.h"
#include "BigBoy.h"

static float spawn_timer;
static float spawn_interval;

void Asteroids_Enemy_Init(BigBoy enemy_pool[], float enemy_width, float enemy_height, Player player)
{
	for (int i = 0; i < 1; i++)
	{
		BigBoy enemy = enemy_pool[i];
		enemy.collider.diameter = (enemy_width + enemy_height) / 2;

		enemy.id = i + 1;
		enemy.parent_id = 0;
		enemy.split_count = 0;

		enemy.active = 0;
		enemy.hp.max = 0;
		enemy.hp.current = 0;

		enemy.pos = CP_Vector_Zero();
		enemy.velocity = CP_Vector_Zero();
		enemy.speed = 0;

		enemy.rotation = 0;
		enemy.rotate_rate = 0;

		enemy.size = 0;
		enemy_pool[i] = enemy;

		spawn_interval = ASTEROIDS_ENEMY_BASE_SPAWN_INTERVAL;
		spawn_timer = spawn_interval;
	}
	Asteroids_Enemy_Spawn(enemy_pool, 1);
}

// Spawn
// Update?
// Hp etc. 
// Colliders
// Draw
// Split
//