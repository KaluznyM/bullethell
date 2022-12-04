#include "camera.h"

void doCamera(void)
{
	if (player != NULL)
	{
		arena.camera.y = player->y - (SCREEN_HEIGHT / 2);
		arena.camera.x = player->x - (SCREEN_WIDTH / 2);
	}
}
