#include "utility.h"
#include "constants.h"

/*
@brief Generates a random position on the screen (window).
*/
CP_Vector generate_random_pos()
{
	float x = (float)(CP_Random_GetInt() % WIN_WIDTH);
	float y = (float)(CP_Random_GetInt() % WIN_HEIGHT);

	return CP_Vector_Set(x, y);
}