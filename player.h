#include "common.h"

extern void addPlayerDeathEffect(void);
extern void firePlayerBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);

extern Program app;
extern Entity *player;
extern Arena arena;