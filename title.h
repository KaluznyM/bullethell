#include "common.h"

extern void bitblit(SDL_Texture *texture, int x, int y, int center);
extern void bitblitRotated(SDL_Texture *texture, int x, int y, float angle);
extern void printText(int x, int y, int r, int g, int b, int align, char *format, ...);
extern void initializeHighscores(void);
extern void initializeArena(void);
extern SDL_Texture *loadTexture(char *filename);

extern Program app;
extern Arena arena;
