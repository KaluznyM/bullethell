#include "player.h"

static void die(void);

static SDL_Texture *playerTexture;

void initializePlayer(void)
{
	playerTexture = loadTexture("graphic/hero.png");
}

void addPlayer(void)
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	arena.entityTail->next = player;
	arena.entityTail = player;
	
	player->texture = playerTexture;
	player->health = 5;
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->radius = 24;
	player->whose = SIDE_PLAYER;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
	player->color.r = player->color.g = player->color.b = player->color.a = 255;
	
	arena.ammo[WPN_PISTOL] = PISTOL_AMMO;
	arena.ammo[WPN_SMG] = SMG_AMMO;
	arena.ammo[WPN_SHOTGUN] = SHOTGUN_AMMO;
	
	player->die = die;
}

void doPlayer(void)
{
	if (player != NULL)
	{
		player->dx *= 0.85;
		player->dy *= 0.85;

		if (app.keyboard[SDL_SCANCODE_ESCAPE])
		{
			cleanup();
			exit(0);
		}

		if (app.keyboard[SDL_SCANCODE_BACKSPACE])
		{
			initializeTitle();
		}

		if (app.keyboard[SDL_SCANCODE_N])
		{
			initializeArena();
		}

		if (app.keyboard[SDL_SCANCODE_UP])
		{
			player->dy = -PLAYER_SPEED;
		}
		
		if (app.keyboard[SDL_SCANCODE_DOWN])
		{
			player->dy = PLAYER_SPEED;
		}
		
		if (app.keyboard[SDL_SCANCODE_LEFT])
		{
			player->dx = -PLAYER_SPEED;
		}
		
		if (app.keyboard[SDL_SCANCODE_RIGHT])
		{
			player->dx = PLAYER_SPEED;
		}
		
		player->angle = getAngle(player->x - arena.camera.x, player->y - arena.camera.y, app.mouse.x, app.mouse.y);
		
		if (player->reload == 0 && arena.ammo[player->weaponType] > 0 && app.mouse.button[SDL_BUTTON_LEFT])
		{
			firePlayerBullet();
			
			arena.ammo[player->weaponType]--;
		}
		
		if (app.mouse.wheel < 0)
		{
			if (--player->weaponType < WPN_PISTOL)
			{
				player->weaponType = WPN_MAX - 1;
			}
			
			app.mouse.wheel = 0;
		}
		
		if (app.mouse.wheel > 0)
		{
			if (++player->weaponType >= WPN_MAX)
			{
				player->weaponType = WPN_PISTOL;
			}
			
			app.mouse.wheel = 0;
		}
		
		if (app.mouse.button[SDL_BUTTON_RIGHT])
		{
			if (player->weaponType == WPN_PISTOL && arena.ammo[WPN_PISTOL] == 0)
			{
				arena.ammo[WPN_PISTOL] = PISTOL_AMMO;
			}
			
			app.mouse.button[SDL_BUTTON_RIGHT] = 0;
		}
	}
}

static void die(void)
{
	addPlayerDeathEffect();
	
	player = NULL;
}
