#include "title.h"

static void logic(void);
static void draw(void);
static void printLogo(void);

static SDL_Texture *arenaTexture;
static int arenaY = -200;	//height of game title fall
static float arenaDY = 0;	//bounce

void initializeTitle(void)
{
	app.handler.logic = logic;
	app.handler.draw = draw;
	
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	memset(&app.mouse, 0, sizeof(Mouse));
	
	arenaTexture = loadTexture("graphic/bullethell.png");
	arenaY = -200;
	arenaDY = 0;
}

static void logic(void)
{
	//acceleration of fall and bouncing
	arenaDY = MIN(arenaDY + 0.25, 25);
	
	arenaY = MIN(arenaY + arenaDY, 200);
	//capping the fall of title
	if (arenaY == 200)
	{
		arenaDY = -arenaDY * 0.5;
		
		if (arenaDY > -1)
		{
			arenaDY = 0;
		}
	}
	//handling input
	if (app.keyboard[SDL_SCANCODE_ESCAPE])
	{
		cleanup();
		exit(0);
	}
	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		initializeArena();
		arena.type = ZERO;
	}
	if (app.mouse.button[SDL_BUTTON_RIGHT])
	{
		initializeHighscores();
	}
	if (app.keyboard[SDL_SCANCODE_1])
	{
		initializeArena();
		arena.type = FIRST;
	}
	if (app.keyboard[SDL_SCANCODE_2])
	{
		initializeArena();
		arena.type = SECOND;
	}
	if (app.keyboard[SDL_SCANCODE_3])
	{
		initializeArena();
		arena.type = THIRD;
	}
}

static void draw(void)
{
	printLogo();

	printText(SCREEN_WIDTH / 2, 500, 255, 255, 255, TEXT_CENTER, "PRESS LPM TO PLAY FREE MODE!");
	printText(SCREEN_WIDTH / 2, 550, 255, 255, 255, TEXT_CENTER, "PRESS RPM TO SEE HIGHSCORES");
	printText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "1-FIRST ARENA 2-SECOND ARENA 3-THIRD ARENA");
}

static void printLogo(void)
{
	bitblit(arenaTexture, SCREEN_WIDTH / 2, arenaY, 1);
}
