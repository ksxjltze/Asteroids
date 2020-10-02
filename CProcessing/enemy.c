#include "enemy.h"

void init_enemies(struct Enemy arr_enemy[], int count, float enemy_width, float enemy_height)
{
	//temp TODO: move somewhere else
	struct Collider_AABB spawn_rect;
	CP_Vector spawn_pos = CP_Vector_Set((float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);
	spawn_rect.width = 200;
	spawn_rect.height = 200;

	for (int i = 0; i < count; i++)
	{
		//test enemy
		struct Enemy enemy = arr_enemy[i];
		enemy.collider.width = enemy_width;
		enemy.collider.height = enemy_height;

		enemy.active = 1;
		enemy.hp.max = ENEMY_HP;
		enemy.hp.current = enemy.hp.max;

		enemy.pos = generate_random_pos();
		while (check_collision_AABB(enemy.collider, enemy.pos, spawn_rect, spawn_pos))
		{
			enemy.pos = generate_random_pos();
		}


		arr_enemy[i] = enemy;

	}

}

void process_enemies(struct Enemy arr_enemy[], int count)
{
	for (int i = 0; i < count; i++)
	{
		struct Enemy* enemy = &arr_enemy[i];
		if (enemy->status.hit)
		{
			enemy->status.hit_cooldown -= CP_System_GetDt();
			if (enemy->status.hit_cooldown <= 0)
			{
				enemy->status.hit = 0;
				enemy->status.hit_cooldown = HURT_WINDOW;
			}
		}

		if (enemy->hp.current <= 0)
		{
			enemy->active = 0;
		}

	}
}

void draw_enemies(struct Enemy arr_enemy[], int count, CP_Image enemy_sprite, float enemy_width, float enemy_height, CP_Image enemy_hurt_sprite, CP_Image health_bar_sprite)
{
	float offset_y = enemy_height / 2 + BAR_HEIGHT + BAR_OFFSET_Y;
	for (int i = 0; i < count; i++)
	{
		struct Enemy enemy = arr_enemy[i];
		if (enemy.active)
		{
			CP_Image_Draw(enemy_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255);
			float percent = enemy.hp.current / enemy.hp.max;
			CP_Image_Draw(health_bar_sprite, enemy.pos.x, enemy.pos.y - offset_y, percent * BAR_WIDTH, BAR_HEIGHT, 255);

			if (enemy.status.hit)
			{
				CP_Image_Draw(enemy_hurt_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255);
			}
		}
	}
}
