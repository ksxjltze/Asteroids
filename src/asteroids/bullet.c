#include "bullet.h"

void Asteroids_Bullet_Init(struct Bullet arr_bullet[], int count, float bullet_width, float bullet_height)
{
	for (int i = 0; i < count; i++)
	{
		struct Bullet bullet = arr_bullet[i];
		bullet.active = 0;
		bullet.pos = CP_Vector_Set(-1, -1);
		bullet.velocity = CP_Vector_Set(0, 0);

		bullet.collider.diameter = (bullet_width + bullet_height) / 2;

		//bullet.collider.width = bullet_width;
		//bullet.collider.height = bullet_height;

		arr_bullet[i] = bullet;
	}
}

void Asteroids_Bullet_Update(struct Bullet arr_bullet[], int bullet_count, struct Enemy arr_enemy[], int enemy_count)
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

			bullet = check_collision_enemy_bullet(arr_enemy, enemy_count, bullet);

			bullet.pos = CP_Vector_Add(bullet.pos, CP_Vector_Scale(bullet.velocity, CP_System_GetDt()));
			arr_bullet[i] = bullet;
		}

	}
}

void Asteroids_Bullet_Draw(struct Bullet arr_bullet[], int count, CP_Image bullet_sprite, float bullet_width, float bullet_height)
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

void Asteroids_Bullet_Debug(struct Bullet arr_bullet[], int count)
{
	for (int i = 0; i < count; i++)
	{
		struct Bullet bullet = arr_bullet[i];
		if (bullet.active)
		{
			//debug_draw_collider_rect(enemy.collider, enemy.pos);
			debug_draw_collider_circle(bullet.collider, bullet.pos);
		}

	}
}