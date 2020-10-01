#pragma once
#include "game.h"
#include "constants.h"

float shoot_cooldown = 0.0f;

CP_Image player_sprite;
CP_Image bullet_sprite;
CP_Image enemy_sprite;
CP_Image enemy_hurt_sprite;
CP_Image health_bar_sprite;
CP_Image player_health_sprite;
CP_Image powerups_sprite;

//player
float player_width;
float player_height;
float player_rotation;

float bullet_width;
float bullet_height;

float enemy_width;
float enemy_height;

float powerups_width;
float powerups_height;

struct Bullet arr_bullet[999];
struct Enemy arr_enemy[5];
struct Heart arr_heart[3];
struct powerups arr_powerups[2];
struct Player player;

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	// initialize variables and CProcessing settings for this gamestate
	settings_setup(WIN_WIDTH, WIN_HEIGHT);
	load_sprites();
	init_entities();
}

//@brief Initializes game entities. Populates entity struct arrays with data (e.g. position, health, etc.)
void init_entities()
{
	//Player
	init_player();

	//TODO: Possibly implement an entity manager to manage different types of entities.
	init_enemies(arr_enemy, sizeof(arr_enemy) / sizeof(arr_enemy[0]), enemy_width, enemy_height);
	init_bullets(arr_bullet, sizeof(arr_bullet) / sizeof(arr_bullet[0]), bullet_width, bullet_height);

	for (int i = 0; i < sizeof(arr_heart) / sizeof(arr_heart[0]); i++)
	{
		//
		struct Heart heart = arr_heart[i];
		heart.pos = CP_Vector_Set((i+1) * 100.0f, 50.0f);
		heart.active = 1;

		arr_heart[i] = heart;

	}

	for (int i = 0; i < sizeof(arr_powerups) / sizeof(arr_powerups[0]); i++)
	{
		struct powerups powerups = arr_powerups[i];
		powerups.pos = generate_random_pos();
		powerups.active = 1;

		powerups.collider.width = powerups_width;
		powerups.collider.height = powerups_height;

		arr_powerups[i] = powerups;

	}

}

//@brief Loads sprites from file path and sets their width and height.
void load_sprites()
{
	player_sprite = CP_Image_Load(PLAYER_SPRITE_PATH);
	bullet_sprite = CP_Image_Load("./Assets/bullet.png");
	enemy_sprite = CP_Image_Load("./Assets/enemy.png");
	health_bar_sprite = CP_Image_Load("./Assets/healthbar.png");
	powerups_sprite = CP_Image_Load("./Assets/powerup.png");
	enemy_hurt_sprite = generate_hurt_sprite(enemy_sprite);
	player_health_sprite = CP_Image_Load("./Assets/heart.png");

	player.pos = CP_Vector_Set((float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	player_width = (float)CP_Image_GetWidth(player_sprite) * 2;
	player_height = (float)CP_Image_GetHeight(player_sprite) * 2;

	bullet_width = (float)CP_Image_GetWidth(bullet_sprite);
	bullet_height = (float)CP_Image_GetHeight(bullet_sprite);

	enemy_width = (float)CP_Image_GetWidth(enemy_sprite) * 3;
	enemy_height = (float)CP_Image_GetHeight(enemy_sprite) * 3;

	powerups_width = (float)CP_Image_GetWidth(powerups_sprite) * 0.3f;
	powerups_height = (float)CP_Image_GetWidth(powerups_sprite) * 0.3f;
}

CP_Image generate_hurt_sprite(CP_Image sprite)
{

	unsigned char* pixels = malloc(CP_Image_GetPixelBufferSize(enemy_sprite));
	CP_Image_GetPixelData(enemy_sprite, pixels);

	//Create Enemy Hurt Sprite from modified enemy_sprite pixel data.
	if (pixels)
	{
		for (int i = 0; i < CP_Image_GetPixelBufferSize(enemy_sprite); ++i)
		{
			if (i % 4 == 3) //alpha
			{
				continue;
			}

			if (i % 4 == 0) //red
			{
				if (pixels[i - 1] > 0)
					pixels[i - 1] = 255;
			}
			else
				pixels[i] = 0;

		}

	}

	return CP_Image_CreateFromData(CP_Image_GetWidth(enemy_sprite), CP_Image_GetHeight(enemy_sprite), pixels);
}

void process_bullets()
{
	//bullet
	for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
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

			for (int j = 0; j < sizeof(arr_enemy) / sizeof(arr_enemy[0]); j++)
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

int check_collision_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2)
{
	//simple collision
	int is_overlap_x = (pos1.x + collider1.width >= pos2.x - collider2.width / 2 && pos2.x + collider2.width / 2 >= pos1.x - collider1.width);
	int is_overlap_y = (pos1.y + collider1.height >= pos2.y - collider2.height / 2 && pos2.y + collider2.height / 2 >= pos1.y - collider1.height);

	if (is_overlap_x && is_overlap_y)
		return 1;

	return 0;
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	// check input, update simulation, render etc.
	check_input();

	if (shoot_cooldown < 0)
		shoot_cooldown = 0;
	else
		shoot_cooldown -= CP_System_GetDt();

	//Process enemies
	for (int i = 0; i < sizeof(arr_enemy) / sizeof(arr_enemy[0]); i++)
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

	process_bullets();

	render();

}

void check_input()
{

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	CP_Vector mousePos = CP_Vector_Set(mouseX, mouseY);
	CP_Vector shoot_direction = CP_Vector_Normalize(CP_Vector_Subtract(mousePos, player.pos));
	CP_Vector vec_up = CP_Vector_Set(0, -1);
	CP_Vector vec_right = CP_Vector_Set(1, 0);
	float dot = CP_Vector_DotProduct(shoot_direction, vec_right);

	if (dot >= 0)
		player_rotation = CP_Vector_Angle(shoot_direction, vec_up);
	else if (dot < 0)
		player_rotation = -CP_Vector_Angle(shoot_direction, vec_up);

	if (CP_Input_KeyDown(KEY_W))
	{
		//velocity.y -= speed;
		player.pos.y -= SPEED;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		//velocity.y += speed;
		player.pos.y += SPEED;
	}

	if (CP_Input_KeyDown(KEY_A))
	{
		//velocity.x -= speed;
		player.pos.x -= SPEED;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		//velocity.x += speed;
		player.pos.x += SPEED;
	}

	if (CP_Input_MouseDown(MOUSE_BUTTON_1))
	{
		if (shoot_cooldown > 0)
			return;

		shoot_cooldown = 60 / FIRE_RATE; //seconds per bullet

		for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
		{
			struct Bullet bullet = arr_bullet[i];
			if (!bullet.active) {
				bullet.pos = CP_Vector_Set(player.pos.x, player.pos.y);
				bullet.velocity = CP_Vector_Set(shoot_direction.x * BULLET_SPEED, shoot_direction.y * BULLET_SPEED);
				bullet.active = 1;

				arr_bullet[i] = bullet;
				break;
			}
		}

	}
}

void display_fps()
{
	//Char buffer
	char fps_str[10];
	//Get FPS
	float fps = roundf(CP_System_GetFrameRate());
	sprintf_s(fps_str, 10, "%d", (int)fps); //Convert int to string

	//Display FPS
	CP_Font_DrawText(fps_str, 100, 100);
}

void render()
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Asteroids", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	display_fps();

	//Render Bullets
	for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
	{
		struct Bullet bullet = arr_bullet[i];
		if (bullet.active) {
			CP_Image_Draw(bullet_sprite, bullet.pos.x, bullet.pos.y, bullet_width, bullet_height, 255);
		}
	}

	//Render Enemies
	for (int i = 0; i < sizeof(arr_enemy) / sizeof(arr_enemy[0]); i++)
	{
		struct Enemy enemy = arr_enemy[i];
		if (enemy.active)
		{
			CP_Image_Draw(enemy_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255);
			float percent = enemy.hp.current / enemy.hp.max;
			CP_Image_Draw(health_bar_sprite, enemy.pos.x, enemy.pos.y - 100, percent * BAR_WIDTH, BAR_HEIGHT, 255);

			if (enemy.status.hit)
			{
				CP_Image_Draw(enemy_hurt_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255);
			}
		}
	}

	// render powerups
	for (int i = 0; i < sizeof(arr_powerups) / sizeof(arr_powerups[0]); i++)
	{
		struct powerups powerups = arr_powerups[i];
		if (powerups.active)
		{
			CP_Image_Draw(powerups_sprite, powerups.pos.x, powerups.pos.y, powerups_width, powerups_height, 255);
		}

	}

	draw_player(player_sprite, player.pos, player_width, player_height, player_rotation);

	//Draw Hearts
	for (int i = 0; i < sizeof(arr_heart) / sizeof(arr_heart[0]); i++)
	{
		if (arr_heart[i].active == 1)
		{
			CP_Image_Draw(player_health_sprite, arr_heart[i].pos.x, arr_heart[i].pos.y, (float)CP_Image_GetWidth(player_health_sprite) * 2,
				(float)CP_Image_GetHeight(player_health_sprite), 255);
		}
	}

	//TEST PLAYER ROTATION
	char buf[100];
	_gcvt_s(buf, 100, player_rotation, 4);

	//Display FPS
	CP_Font_DrawText(buf, 300, 100);

}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}