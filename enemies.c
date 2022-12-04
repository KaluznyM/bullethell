#include "enemies.h"

static void type1(void);
static void type2(void);
static void type3(void);
static void die(void);

static SDL_Texture *enemyTexture[3];

void initializeEnemies(void)
{
	enemyTexture[0] = loadTexture("graphic/enemy01.png");
	enemyTexture[1] = loadTexture("graphic/enemy02.png");
	enemyTexture[2] = loadTexture("graphic/enemy03.png");
}

void addEnemy(int x, int y)
{
	Entity *entity;
	
	entity = malloc(sizeof(Entity));
	memset(entity, 0, sizeof(Entity));
	arena.entityTail->next = entity;
	arena.entityTail = entity;
	
	entity->whose = SIDE_ENEMY;
	entity->x = x;
	entity->y = y;
	
	entity->color.r = entity->color.g = entity->color.b = entity->color.a = 255;
	//if other arena than free mode is selected spawn only one enemy
	if (arena.type) 
	{
		switch (arena.type)	
		{
		case 1:
			entity->texture = enemyTexture[0];
			entity->type = type1;
			entity->radius = 35;
			entity->health = 250;
			break;

		case 2:
			entity->texture = enemyTexture[1];
			entity->type = type2;
			entity->radius = 50;
			entity->health = 100;
			break;

		case 3:
			entity->texture = enemyTexture[2];
			entity->type = type3;
			entity->radius = 22;
			entity->health = 500;
			break;
		}
	}
	//in free mode (arena.type==ZERO==0) spawn many enemies
	else
	{
		switch (rand() % 10)		//add empty cases to spawn less enemies
		{
		case 2:
			entity->texture = enemyTexture[1];
			entity->type = type2;
			entity->radius = 50;
			entity->health = 30;
			break;

		case 4:
			entity->texture = enemyTexture[2];
			entity->type = type3;
			entity->radius = 22;
			entity->health = 1;
			break;
		case 6:

		default:
			entity->texture = enemyTexture[0];
			entity->type = type1;
			entity->radius = 35;
			entity->health = 6;
			break;
		}
	}
	SDL_QueryTexture(entity->texture, NULL, NULL, &entity->w, &entity->h);
	
	entity->die = die;
}

static void type1(void)	//yellow
{
	if (player != NULL)
	{
		self->angle = getAngle(self->x, self->y, player->x, player->y);
		
		calcTilt(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
		
		if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_HEIGHT - 200)
		{

			for (int i = -120; i <= 120; i = i + 80)
			{
				fireEnemyBullet(FIRST, i, i);
			}
			self->reload = FPS;
		}
	}
}

static void type2(void)	//red
{
	float dx, dy;
	
	if (++self->angle >= 360)
	{
		self->angle = 0;
	}
	
	if (player != NULL)
	{
		calcTilt(player->x, player->y, self->x, self->y, &dx, &dy);
		
		dx /= 10;
		dy /= 10;
		
		self->dx += dx;
		self->dy += dy;
		
		self->dx = MAX(MIN(self->dx, 3), -3);
		self->dy = MAX(MIN(self->dy, 3), -3);
		
		if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_HEIGHT / 2)
		{
			for (int i = -100; i <= 100; i = i + 200)
			{
				fireEnemyBullet(SECOND, i, i);
			}
			self->reload = 2;
		}
	}
}

static void type3(void)	//violet
{
	float dx, dy;
	
	self->angle -= 5;
	
	if (self->angle < 0)
	{
		self->angle = 359;
	}
	
	if (player != NULL)
	{
		calcTilt(player->x, player->y, self->x, self->y, &dx, &dy);
		
		dx /= 10;
		dy /= 10;
		
		self->dx += dx;
		self->dy += dy;
		
		self->dx = MAX(MIN(self->dx, 5), -5);
		self->dy = MAX(MIN(self->dy, 5), -5);
		
		if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_HEIGHT)
		{
			for (int i = -ARENA_WIDTH * 1.2; i <= ARENA_WIDTH * 1.2; i = i + 1000)
			{
				fireEnemyBullet(THIRD, i, -ARENA_WIDTH * 2);
				fireEnemyBullet(THIRD, i, ARENA_WIDTH * 2);
				fireEnemyBullet(THIRD, -ARENA_WIDTH * 2, i);
				fireEnemyBullet(THIRD, ARENA_WIDTH * 2, i);
			}
			fireEnemyBullet(SECOND, 0, 0);

			self->reload = FPS/1.5;
		}
	}
}

static void die(void)
{
	addEnemyDeathEffect();	
	arena.score += 10;
}
