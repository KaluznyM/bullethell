#include "common.h"

extern void addEnemyDeathEffect(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void calcTilt(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void fireEnemyBullet(int enemyType, int dirX, int dirY);
extern int getDistance(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);

extern Arena arena;
extern Time time;
extern Entity *player;
extern Entity *self;
