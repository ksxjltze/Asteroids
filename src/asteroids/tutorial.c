#include "tutorial.h"
#include "player.h"
#include "constants.h"

Player player;
CP_Image player_sprite;

void Asteroids_Tutorial_Init()
{
	player_sprite = CP_Image_Load(ASTEROIDS_PLAYER_SPRITE_PATH_DEFAULT);
	player = Asteroids_Player_Init(ASTEROIDS_PLAYER_SPRITE_WIDTH, ASTEROIDS_PLAYER_SPRITE_HEIGHT, false);
	
}

void Asteroids_Tutorial_Update()
{
	Asteroids_Player_Update(&player);
	Asteroids_Player_Draw(player_sprite, player.pos, ASTEROIDS_PLAYER_SPRITE_WIDTH, ASTEROIDS_PLAYER_SPRITE_HEIGHT, 255, player.rotation);
}

void Asteroids_Tutorial_Exit()
{

}