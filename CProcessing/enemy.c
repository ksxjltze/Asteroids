#include "enemy.h"

void init_enemies(struct Enemy arr_enemy[], int count, float enemy_width, float enemy_height)
{
	for (int i = 0; i < count; i++)
	{
		//test enemy
		struct Enemy enemy = arr_enemy[i];
		enemy.pos = generate_random_pos();
		enemy.active = 1;
		enemy.hp.max = 100;
		enemy.hp.current = enemy.hp.max;

		enemy.collider.width = enemy_width;
		enemy.collider.height = enemy_height;

		arr_enemy[i] = enemy;

	}

}