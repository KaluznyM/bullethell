#include "common.h"

extern void bitblit(SDL_Texture *texture, int x, int y, int center);
extern SDL_Texture *loadTexture(char *filename);

extern Program app;
extern Arena arena;
extern Entity *self;
