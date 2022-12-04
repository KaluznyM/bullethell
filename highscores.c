#include "highscores.h"

static void logic(void);
static void draw(void);
static int highscoreComparator(const void *a, const void *b);
static void drawHighscores(void);
static void doNameInput(void);
static void drawNameInput(void);

static Highscore *newHighscore;
static int cursorBlink;

void initializeHighscoreTable(void)
{
	int i;
	
	memset(&highscores, 0, sizeof(Highscores));
	
	for (i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		highscores.highscore[i].score = (NUM_HIGHSCORES - i) * 0;
		STRNCPY(highscores.highscore[i].name, "NAME", MAX_SCORE_NAME_LENGTH);
	}
	
	newHighscore = NULL;
	cursorBlink = 0;
}

void initializeHighscores(void)
{
	app.handler.draw = draw;
	app.handler.logic = logic;
	
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	memset(&app.mouse, 0, sizeof(Mouse));
}

static void logic(void)
{
	if (newHighscore != NULL)
	{
		doNameInput();
	}
	else
	{
		if (app.mouse.button[SDL_BUTTON_RIGHT])
		{
			initializeTitle();
		}
		
		if (app.mouse.button[SDL_BUTTON_LEFT])
		{
			initializeArena();
		}
		if (app.keyboard[SDL_SCANCODE_ESCAPE])
		{
			cleanup();
			exit(0);
		}

	}
	
	if (++cursorBlink >= FPS)
	{
		cursorBlink = 0;
	}
}

static void doNameInput(void)
{
	int nameLength;
	char c;

	nameLength = strlen(newHighscore->name);
	//uppercasing every character
	for (int i = 0 ; i < strlen(app.inputText) ; i++)
	{
		c = toupper(app.inputText[i]);
		//check if name is shorter than max name length and check if current character is a letter
		if (nameLength < MAX_SCORE_NAME_LENGTH - 1 && c >= ' ' && c <= 'Z')
		{
			//add name letter by letter to new highscore
			newHighscore->name[nameLength++] = c;
		}
	}
	//check if enter is pressed and delete it from the name
	if (nameLength > 0 && app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		newHighscore->name[--nameLength] = '\0';
		
		app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
	}
	//check if player entered anything if not he is called PLAYER
	if (app.keyboard[SDL_SCANCODE_RETURN])
	{
		if (strlen(newHighscore->name) == 0)
		{
			STRNCPY(newHighscore->name, "PLAYER", MAX_SCORE_NAME_LENGTH);
		}
		
		newHighscore = NULL;
	}
}

static void draw(void)
{
	if (newHighscore != NULL)
	{
		drawNameInput();
	}
	else
	{
		drawHighscores();

		printText(SCREEN_WIDTH / 2, 615, 255, 255, 255, TEXT_CENTER, "PRESS LPM TO PLAY!");
		printText(SCREEN_WIDTH / 2, 665, 255, 255, 255, TEXT_CENTER, "PRESS RPM TO SEE TITLE SCREEN");
	}
}

static void drawNameInput(void)
{
	SDL_Rect r;
	
	printText(SCREEN_WIDTH / 2, 70, 255, 255, 255, TEXT_CENTER, "YOU'VE REACHED A NEW HIGHSCORE!");
	printText(SCREEN_WIDTH / 2, 120, 255, 255, 255, TEXT_CENTER, "ENTER YOUR NAME BELOW:");
	printText(SCREEN_WIDTH / 2, 250, 128, 255, 128, TEXT_CENTER, newHighscore->name);
	//drawing the cursor at the end of input
	if (cursorBlink < FPS / 2)
	{
		//checking where to draw it
		r.x = ((SCREEN_WIDTH / 2) + (strlen(newHighscore->name) * GLYPH_WIDTH) / 2) + 5;
		r.y = 250;
		r.w = GLYPH_WIDTH;
		r.h = GLYPH_HEIGHT;
		//drawing a rectangle
		SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(app.renderer, &r);
	}
	
	printText(SCREEN_WIDTH / 2, 625, 255, 255, 255, TEXT_CENTER, "PRESS ENTER TO CONTINUE");
}

static void drawHighscores(void)
{
	int i, y, r, g, b;
	
	y = 150;
	
	printText(SCREEN_WIDTH / 2, 70, 255, 255, 255, TEXT_CENTER, "HIGHSCORES");
	//iterating over each highscore and drawing them
	for (i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		r = 250;
		g = 250;
		b = 250;
		
		if (highscores.highscore[i].recent)
		{
			b = 0;
		}
		//drawing a name with up to 20 spaces in between the name and score
		printText(SCREEN_WIDTH / 2, y, r, g, b, TEXT_CENTER, "#%d. %-20s ..... %06d", (i + 1), highscores.highscore[i].name, highscores.highscore[i].score);
		
		y += 45;
	}
}

void addHighscore(int score)
{
	Highscore newScore[NUM_HIGHSCORES + 1];
	int i;
	
	memset(newScore, 0, sizeof(Highscore) * (NUM_HIGHSCORES + 1));
	//copy all the existing highscores into an array
	for (i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		newScore[i] = highscores.highscore[i];
		newScore[i].recent = 0;
	}
	
	newScore[NUM_HIGHSCORES].score = score;
	newScore[NUM_HIGHSCORES].recent = 1;
	//sorting all scores to place new one where it should be
	qsort(newScore, NUM_HIGHSCORES + 1, sizeof(Highscore), highscoreComparator);
	
	newHighscore = NULL;
	//iterate over each highscore and save them in order
	for (i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		highscores.highscore[i] = newScore[i];
		
		if (highscores.highscore[i].recent)
		{
			newHighscore = &highscores.highscore[i];
		}
	}
}

static int highscoreComparator(const void *a, const void *b)
{
	Highscore *h1 = ((Highscore*)a);
	Highscore *h2 = ((Highscore*)b);

	return h2->score - h1->score;
}
