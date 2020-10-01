#include "bullet.h"

void init_bullets(struct Bullet arr_bullet[], int count, float bullet_width, float bullet_height)
{
	for (int i = 0; i < count; i++)
	{
		struct Bullet bullet = arr_bullet[i];
		bullet.active = 0;
		bullet.pos = CP_Vector_Set(-1, -1);
		bullet.velocity = CP_Vector_Set(0, 0);

		bullet.collider.width = bullet_width;
		bullet.collider.height = bullet_height;

		arr_bullet[i] = bullet;
	}
}

void process_bullets(struct Bullet arr_bullet[], int bullet_count, struct Enemy arr_enemy[], int enemy_count)
{
	//bullet
	for (int i = 0; i < bullet_count; i++)
	{
		struct Bullet bullet = arr_bullet[i];
		if (bullet.active)
		{
			if ((bullet.pos.x > WIN_WIDTH || bullet.pos.x < 0) && (bullet.pos.y > WIN_HEIGHT || bullet.pos.y < 0))
			{
				bullet.active = 0;
				bullet.pos = CP_Vector_Set(-1, -1);
				bullet.velocity = CP_Vector_Set(0, 0);

				arr_bullet[i] = bullet;
				continue;
			}

			for (int j = 0; j < enemy_count; j++)
			{
				if (!arr_enemy[j].active)
					continue;

				struct Enemy* enemy = &arr_enemy[j];
				if (check_collision_AABB(bullet.collider, bullet.pos, enemy->collider, enemy->pos))
				{
					bullet.active = 0;
					bullet.pos = CP_Vector_Set(-1, -1);
					bullet.velocity = CP_Vector_Set(0, 0);

					if (!enemy->status.hit)
					{
						enemy->status.hit = 1;
						enemy->hp.current -= 10;
					}
				}
			}

			bullet.pos = CP_Vector_Add(bullet.pos, CP_Vector_Scale(bullet.velocity, CP_System_GetDt()));
			arr_bullet[i] = bullet;
		}

	}
}

void draw_bullets(struct Bullet arr_bullet[], int count, CP_Image bullet_sprite, float bullet_width, float bullet_height)
{
	//Render Bullets
	for (int i = 0; i < count; i++)
	{
		struct Bullet bullet = arr_bullet[i];
		if (bullet.active) {
			CP_Image_Draw(bullet_sprite, bullet.pos.x, bullet.pos.y, bullet_width, bullet_height, 255);
		}
	}
}