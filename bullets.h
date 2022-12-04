#include "common.h"

extern void addBulletHitEffect(Entity *b);
extern void bitblitRotated(SDL_Texture *texture, int x, int y, float angle);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
extern void calcTilt(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern SDL_Texture *loadTexture(char *filename);

extern Arena arena;
extern Program app;
extern Time time;
extern Entity *player;
extern Entity *self;
