#include "arena.h"

static void draw(void);
static void logic(void);
static void drawBoard(void);
static void drawStats(void);
static void drawTime(char* name, double time, int x, int y);
static void drawWeaponInfo(char *name, int type, int x, int y);
static void newArena(void);
static void spawnEnemy(void);

static int enemySpawnTimer;	//time after which enemies will spawn
static int gameOverTimer;	//time after which game over screen is shown (to show death animations)
static int scoreDisplay;	//displayed score
static SDL_Texture *crosshairTexture;
static SDL_Texture *floorTexture[4];

void initializeArena(void)
{
	time.worldTime = 0;
	app.handler.logic = logic;
	app.handler.draw = draw;
	
	crosshairTexture = loadTexture("graphic/crosshair.png");
	floorTexture[ZERO] = loadTexture("graphic/floor.png");
	floorTexture[FIRST] = loadTexture("graphic/level1.png");
	floorTexture[SECOND] = loadTexture("graphic/level2.png");
	floorTexture[THIRD] = loadTexture("graphic/level3.png");
	
	newArena();
	addPlayer();
	
	enemySpawnTimer = 0;
	scoreDisplay = 0;
	
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	memset(&app.mouse, 0, sizeof(Mouse));
}

static void newArena(void)
{
	Entity *entity;
	Effect *effect;
	//freeing all entities
	while (arena.entityHead.next)
	{
		entity = arena.entityHead.next;
		arena.entityHead.next = entity->next;
		free(entity);
	}
	
	while (arena.bulletHead.next)
	{
		entity = arena.bulletHead.next;
		arena.bulletHead.next = entity->next;
		free(entity);
	}
	
	while (arena.effectHead.next)
	{
		effect = arena.effectHead.next;
		arena.effectHead.next = effect->next;
		free(effect);
	}
	
	memset(&arena, 0, sizeof(Arena));
	
	arena.entityTail = &arena.entityHead;
	arena.bulletTail = &arena.bulletHead;
	arena.effectTail = &arena.effectHead;
	
	gameOverTimer = FPS * 2;	//time after which game over screen is shown (to show death animations)
}

static void logic(void)
{
	doPlayer();
	doCamera();
	doEntities();
	doBullets();
	spawnEnemy();
	doEffects();

	if (arena.score > 999999)
	{
		player->health = 0;
	}
	if (scoreDisplay < arena.score)
	{
		scoreDisplay = arena.score;
	}
	if (player == NULL && --gameOverTimer <= 0)
	{
		addHighscore(arena.score);
		initializeHighscores();
	}
}

static void spawnEnemy(void)
{
	int x, y;
	//for arena 1,2,3 we spawn only one enemy in the middle
	if (arena.type && enemySpawnTimer <= 0)
	{
		addEnemy(ARENA_WIDTH/2, ARENA_HEIGHT/2);
		enemySpawnTimer = 1;
	}
	//for free mode we spawn infinitely many enemies on random tiles
	else if (!arena.type) {
		if (player != NULL && --enemySpawnTimer <= 0 && !arena.type)
		{
			y = player->y + (rand() % SCREEN_HEIGHT) - (rand() % SCREEN_HEIGHT);
			x = player->x + (rand() % SCREEN_WIDTH) - (rand() % SCREEN_WIDTH);
			if (getDistance(x, y, player->x, player->y) > SCREEN_WIDTH / 2)
			{
				addEnemy(x, y);
				//ensure random spawn time
				enemySpawnTimer = (FPS / 2) + rand() % FPS;
			}
		}
	}
}

static void draw(void)
{
	drawStats();
	drawBoard();
	drawEntities();
	drawBullets();
	drawEffects();
	
	bitblit(crosshairTexture, app.mouse.x, app.mouse.y, 1);
}

static void drawStats(void)
{
	printText(10, 10, 255, 255, 255, TEXT_LEFT, "HEALTH:%d", player != NULL ? player->health : 0);
	
	printText(250, 10, 255, 255, 255, TEXT_LEFT, "SCORE:%05d", scoreDisplay);
	
	drawWeaponInfo("PISTOL", WPN_PISTOL, 550, 15);
	
	drawWeaponInfo("SMG", WPN_SMG, 800, 15);
	
	drawWeaponInfo("SHOTGUN", WPN_SHOTGUN, 1050, 15);

	drawTime("TIME", time.worldTime, 10, 690);
}

static void drawTime(char* name, double time, int x, int y)
{
	int r, g, b;

	if (player != NULL)
	{
		r = 0;
		b = 0;
		g = 255;
	}
	else
	{
		r = 205;
		g = 205;
		b = 205;
	}
	printText(x, y, r, g, b, TEXT_LEFT, "%s:%.3f", name, time);
}

static void drawWeaponInfo(char *name, int type, int x, int y)
{
	int r, g, b;
	
	if (player != NULL && player->weaponType == type)
	{
		r = 0;
		b = 255;
		g = 0;
	}
	else
	{
		r = 205;
		g = 205;
		b = 205;
	}
	
	printText(x, y, r, g, b, TEXT_LEFT, "%s:%03d", name, arena.ammo[type]);
}

static void drawBoard(void)
{
	int startingX, endingX, startingY, endingY, x, y, mx, my;
	//finding starting point of screen
	startingX = (arena.camera.x % BOARD_SIZE) * -1;
	endingX = startingX + BOARD_RENDER_WIDTH * BOARD_SIZE + (startingX != 0 ? BOARD_SIZE : 0);

	startingY = (arena.camera.y % BOARD_SIZE) * -1;
	endingY = startingY + BOARD_RENDER_HEIGHT * BOARD_SIZE + (startingY != 0 ? BOARD_SIZE : 0);
	
	mx = arena.camera.x / BOARD_SIZE;
	my = arena.camera.y / BOARD_SIZE;
	//drawing the board as a rectangel using 2 for loops of each dimension
	for (x = startingX; x < endingX; x += BOARD_SIZE)
	{
		for (y = startingY; y < endingY; y += BOARD_SIZE)
		{
			if (mx >= 0 && my >= 0 && mx <= (ARENA_WIDTH / BOARD_SIZE) - 1 && my <= (ARENA_HEIGHT / BOARD_SIZE) - 1)
			{
				bitblit(floorTexture[arena.type], x, y, 0);
			}
			my++;
		}
		my = arena.camera.y / BOARD_SIZE;
		mx++;
	}
}
