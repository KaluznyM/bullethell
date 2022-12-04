#include "main.h"

static void capFrameRate(long *then, float *remainder);
void handleTime(void);

int main(int argc, char *argv[])
{
	long then;
	float remainder;

	memset(&app, 0, sizeof(Program));
	app.textureTail = &app.textureHead;
	
	initializeSDL();
	
	atexit(cleanup);
	
	initializeGame();
	
	initializeTitle();
	
	then = SDL_GetTicks();
	
	remainder = 0;
	time.worldTime = 0;
	time.t1 = SDL_GetTicks();

	while (1)
	{
		handleTime();

		prepareScene();
		
		doInput();

		app.handler.logic();
		
		app.handler.draw();
		
		presentScene();
		
		capFrameRate(&then, &remainder);
	}

	return 0;
}

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;
	wait = 16 + *remainder;
	*remainder -= (int)*remainder;
	frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);
	*remainder += 0.667;
	*then = SDL_GetTicks();
}

void handleTime(void){
	time.t2 = SDL_GetTicks();
	time.delta = (time.t2 - time.t1) * 0.001;
	time.worldTime += time.delta;
	time.t1 = time.t2;
}


