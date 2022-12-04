#include "common.h"

extern void cleanup(void);
extern void doInput(void);
extern void initializeGame(void);
extern void initializeSDL(void);
extern void initializeTitle(void);
extern void prepareScene(void);
extern void presentScene(void);

Program app;
Entity *player;
Entity *self;
Highscores highscores;
Arena arena;
Time time;
