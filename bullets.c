#include "bullets.h"

static void firePlayerSMG(void);
static void firePlayerShotgun(void);
static void firePlayerPistol(void);
static void bulletHitEntity(Entity *b);

static SDL_Texture *bulletTexture;

void initializeBullets(void)
{
	bulletTexture = loadTexture("graphic/bullet.png");
}

void doBullets(void)
{
	Entity *bullet, *prev;
	
	prev = &arena.bulletHead;
	
	for (bullet = arena.bulletHead.next ; bullet != NULL ; bullet = bullet->next)
	{
		bullet->x += bullet->dx;
		bullet->y += bullet->dy;
		
		bulletHitEntity(bullet);
		
		if (--bullet->health <= 0)
		{
			if (bullet == arena.bulletTail)
			{
				arena.bulletTail = prev;
			}
			
			prev->next = bullet->next;
			free(bullet);
			bullet = prev;
		}
		
		prev = bullet;
	}
}

static void bulletHitEntity(Entity *bullet)
{
	//stepping over each entity to see if it got hit by checking collision
	Entity *enitity;
	int distance;
	for (enitity = arena.entityHead.next ; enitity != NULL ; enitity = enitity->next)
	{
		if (enitity->whose != SIDE_NONE && enitity->whose != bullet->whose)
		{
			distance = getDistance(enitity->x, enitity->y, bullet->x, bullet->y);
			if (distance < enitity->radius + bullet->radius)
			{
				//if entity is a player we decrease score
				if (enitity == player) 
				{
					arena.score = arena.score - 1;
					if (time.worldTime - time.hitTime < INVINCIBILITY) 
					{
						bullet->health = 0;
						return;
					}
				}
				//if entity is an enemy we increase score
				else 
				{
					arena.score = arena.score + 1;
				}
				bullet->health = 0;
				enitity->health--;
				addBulletHitEffect(bullet);		
				time.hitTime = time.worldTime;
				return;
			}
		}
	}
}

void drawBullets(void)
{
	Entity *bullet;
	
	for (bullet = arena.bulletHead.next ; bullet != NULL ; bullet = bullet->next)
	{
		SDL_SetTextureColorMod(bullet->texture, bullet->color.r, bullet->color.g, bullet->color.b);
		
		bitblitRotated(bullet->texture, bullet->x - arena.camera.x, bullet->y - arena.camera.y, bullet->angle);
	}
}

void firePlayerBullet(void)
{
	switch (player->weaponType)
	{
		case WPN_SHOTGUN:
			firePlayerShotgun();
			break;

		case WPN_SMG:
			firePlayerSMG();
			break;
			
		default:
			firePlayerPistol();
			break;
	}
}

static Entity *createPlayerBullet(void)
{
	Entity *bullet;
	
	bullet = malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	arena.bulletTail->next = bullet;
	arena.bulletTail = bullet;

	bullet->y = player->y;
	bullet->x = player->x;
	bullet->health = FPS * 2;
	bullet->texture = bulletTexture;
	bullet->radius = 16;
	bullet->angle = player->angle;
	bullet->whose = SIDE_PLAYER;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	bullet->color.r = 128;
	bullet->color.g = 255;
	bullet->color.b = 255;
	bullet->color.a = 255;
	
	return bullet;
}

static void firePlayerShotgun(void)
{
	Entity *bullet;
	int i, destX, destY;
	float dx, dy;
	
	calcTilt(app.mouse.x, app.mouse.y, player->x - arena.camera.x, player->y - arena.camera.y, &dx, &dy);
	
	dx = player->x + (dx * 128);
	dy = player->y + (dy * 128);
	//iiterate over every bullet setting its angle and direction which is random
	for (i = 0 ; i < SHOTGUN_AMMO; i++)
	{
		bullet = createPlayerBullet();

		destY = dy + (rand() % 24 - rand() % 24);
		destX = dx + (rand() % 24 - rand() % 24);
		
		calcTilt(destX, destY, bullet->x, bullet->y, &bullet->dx, &bullet->dy);

		bullet->dy *= 16;
		bullet->dx *= 16;
	}
	
	player->reload = FPS * 0.75;
}

static void firePlayerSMG(void)
{
	Entity* bullet;

	bullet = createPlayerBullet();

	calcTilt(app.mouse.x, app.mouse.y, bullet->x - arena.camera.x, bullet->y - arena.camera.y, &bullet->dx, &bullet->dy);

	bullet->dy *= 16;
	bullet->dx *= 16;

	player->reload = 3;
}

static void firePlayerPistol(void)
{
	Entity *bullet;
	
	bullet = createPlayerBullet();
	
	calcTilt(app.mouse.x, app.mouse.y, bullet->x - arena.camera.x, bullet->y - arena.camera.y, &bullet->dx, &bullet->dy);

	bullet->dy *= 16;
	bullet->dx *= 16;
	
	player->reload = 15;
}

void fireEnemyBullet(int enemyType, int dirX, int dirY)
{
	//angle between enemy and player is calculated and direction of the bullet is set
	Entity *bullet;
	
	bullet = malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	arena.bulletTail->next = bullet;
	arena.bulletTail = bullet;

	bullet->y = self->y;
	bullet->x = self->x;
	bullet->health = FPS * 2;
	bullet->texture = bulletTexture;
	bullet->radius = 16;
	bullet->angle = getAngle(self->x, self->y, player->x, player->y);
	bullet->whose = SIDE_ENEMY;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	bullet->color.r = 255;
	bullet->color.g = 0;
	bullet->color.b = 0;
	bullet->color.a = 255;
	switch (enemyType)
	{
	case 3:
		calcTilt( dirX, dirY, bullet->x, bullet->y, &bullet->dx, &bullet->dy);
	default:
		calcTilt(player->x + dirX, player->y + dirY, bullet->x, bullet->y, &bullet->dx, &bullet->dy);
		break;
	}
	
	bullet->dx *= 12;
	bullet->dy *= 12;
}
