#include "common.h"

extern void addEnemy(int x, int y);
extern void addHighscore(int score);
extern void addPlayer(void);
extern void bitblit(SDL_Texture *texture, int x, int y, int center);
extern void doBullets(void);
extern void doPlayer(void);
extern void doCamera(void);
extern void doEffects(void);
extern void doEntities(void);
extern int getDistance(int x1, int y1, int x2, int y2);
extern void printText(int x, int y, int r, int g, int b, int align, char* format, ...);
extern void initializeHighscores(void);
extern void drawBullets(void);
extern void drawEffects(void);
extern void drawEntities(void);
extern SDL_Texture *loadTexture(char *filename);

extern Program app;
extern Arena arena;
extern Time time;
extern Entity *player;