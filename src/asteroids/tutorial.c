#include "tutorial.h"
#include "player.h"
#include "constants.h"
#include "game.h"
#include "audio_manager.h"
#include "utility.h"
#include "state.h"
#include "bullet.h"
#include "enemy.h"

Player player;
CP_Image player_sprite;
CP_Image bullet_sprite;
CP_Image enemy_sprite;
CP_Image enemy_hurt_sprite;

static float bullet_width;
static float bullet_height;

static float enemy_width;
static float enemy_height;

static float text_row_width;
State tutorialState;
Bullet bullet_pool[ASTEROIDS_POOLSIZE_BULLETS];
Enemy enemy_pool[ASTEROIDS_POOLSIZE_ENEMIES];

enum tutorialStateType { TUTORIAL_MOVE };

void Asteroids_Tutorial_Init(void)
{
	player_sprite = CP_Image_Load(ASTEROIDS_PLAYER_SPRITE_PATH_DEFAULT);
	player = Asteroids_Player_Init(ASTEROIDS_PLAYER_SPRITE_WIDTH, ASTEROIDS_PLAYER_SPRITE_HEIGHT, false);
	text_row_width = 100;

	bullet_sprite = CP_Image_Load("./Assets/bullet_long.png");
	bullet_width = (float)CP_Image_GetWidth(bullet_sprite);
	bullet_height = (float)CP_Image_GetHeight(bullet_sprite);

	Asteroids_Bullet_Init(bullet_pool, ASTEROIDS_POOLSIZE_BULLETS, bullet_width, bullet_height);

	enemy_sprite = CP_Image_Load("./Assets/asteroids_cropped.png");
	enemy_width = (float)ASTEROIDS_ENEMY_BASE_DIAMETER;
	enemy_height = (float)ASTEROIDS_ENEMY_BASE_DIAMETER;

	Asteroids_Enemy_Init(enemy_pool, ASTEROIDS_POOLSIZE_ENEMIES, enemy_width, enemy_height, player);

	tutorialState.id = TUTORIAL_MOVE;
	tutorialState.name = "MOVE";
	tutorialState.action = &Asteroids_Tutorial_State_Move_Tutorial;
	Asteroids_Audio_Manager_Init();
}

void Asteroids_Tutorial_Update(void)
{
	Asteroids_Check_Input(&player, bullet_pool);
	Asteroids_Player_Update(&player);
	Asteroids_Tutorial_Draw();
	Asteroids_Bullet_Update(bullet_pool, ASTEROIDS_POOLSIZE_BULLETS, enemy_pool, ASTEROIDS_POOLSIZE_ENEMIES, player);
	Asteroids_Bullet_Draw(bullet_pool, ASTEROIDS_POOLSIZE_BULLETS, bullet_sprite, bullet_width, bullet_height);
	Asteroids_Player_Draw(player_sprite, player.pos, ASTEROIDS_PLAYER_SPRITE_WIDTH, ASTEROIDS_PLAYER_SPRITE_HEIGHT, 255, player.rotation);
	Asteroids_Tutorial_State_Update();

}

void Asteroids_Tutorial_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
}

void Asteroids_Tutorial_State_Update()
{
	tutorialState.action(&player);
}

void Asteroids_Tutorial_State_Move_Tutorial(void* context)
{
	if (context)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		Asteroids_Tutorial_DrawText(Asteroids_Utility_GetWindowMiddle(), "TEST");
	}
}

void Asteroids_Tutorial_DrawText(CP_Vector pos, const char* text)
{
	CP_Font_DrawTextBox(text, pos.x, pos.y, text_row_width);
}

void Asteroids_Tutorial_Exit(void)
{
	Asteroids_Audio_Manager_Exit();
}