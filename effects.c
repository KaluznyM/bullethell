#include "effects.h"

static SDL_Texture *whiteSquare16;
static SDL_Texture *whiteSquare8;

void initializeEffects(void)
{
	whiteSquare16 = loadTexture("graphic/whiteSquare16.png");
	whiteSquare8 = loadTexture("graphic/whiteSquare8.png");
}

//iterate through every effect and decrease effect's life and alpha(visibility) reducing it to 0
void doEffects(void)
{
	Effect *effect, *prev;
	
	prev = &arena.effectHead;
	
	for (effect = arena.effectHead.next ; effect != NULL ; effect = effect->next)
	{
		//moving an effect
		effect->x += effect->dx;
		effect->y += effect->dy;
		//reducing alpha
		effect->color.a = MAX(effect->color.a - 1, 0);
		//reducing health and checking if equal to 0
		if (--effect->life < 1)
		{
			if (effect == arena.effectTail)
			{
				arena.effectTail = prev;
			}
			
			prev->next = effect->next;
			free(effect);
			effect = prev;
		}
		
		prev = effect;
	}
}

void drawEffects(void)
{
	Effect *effect;
	
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
	
	for (effect = arena.effectHead.next ; effect != NULL ; effect = effect->next)
	{
		SDL_SetTextureBlendMode(effect->texture, SDL_BLENDMODE_ADD);
		
		SDL_SetTextureColorMod(effect->texture, effect->color.r, effect->color.g, effect->color.b);
		SDL_SetTextureAlphaMod(effect->texture, effect->color.a);
		
		bitblit(effect->texture, effect->x - arena.camera.x, effect->y - arena.camera.y, 1);
	}
	
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

void addEnemyDeathEffect(void)
{
	Effect *effect;
	int i;
	
	for (i = 0 ; i < 128 ; i++)
	{
		effect = malloc(sizeof(Effect));
		memset(effect, 0, sizeof(Effect));
		arena.effectTail->next = effect;
		arena.effectTail = effect;
		
		effect->x = self->x;
		effect->y = self->y;
		effect->dx = 400 - rand() % 800;
		effect->dy = 400 - rand() % 800;
		
		effect->dx /= 100;
		effect->dy /= 100;
		
		effect->texture = whiteSquare16;
		
		effect->color.r = 255;
		effect->color.g = 128 + rand() % 128;
		effect->color.b = 0;
		effect->color.a = rand() % 255;
		
		effect->life = rand() % FPS;
	}
}

void addPlayerDeathEffect(void)
{
	Effect *effect;
	int i;
	
	for (i = 0 ; i < 128 ; i++)
	{
		effect = malloc(sizeof(Effect));
		memset(effect, 0, sizeof(Effect));
		arena.effectTail->next = effect;
		arena.effectTail = effect;
		
		effect->x = self->x;
		effect->y = self->y;
		effect->dx = 400 - rand() % 800;
		effect->dy = 400 - rand() % 800;
		
		effect->dx /= 100;
		effect->dy /= 100;
		
		effect->texture = whiteSquare16;
		
		effect->color.r = rand() % 128;
		effect->color.g = 128 + rand() % 128;
		effect->color.b = 255;
		effect->color.a = rand() % 255;
		
		effect->life = rand() % FPS;
	}
}

void addBulletHitEffect(Entity *b)
{
	Effect *effect;
	int i;
	
	for (i = 0 ; i < 16 ; i++)
	{
		effect = malloc(sizeof(Effect));
		memset(effect, 0, sizeof(Effect));
		arena.effectTail->next = effect;
		arena.effectTail = effect;
		
		effect->x = b->x;
		effect->y = b->y;
		effect->dx = 400 - rand() % 800;
		effect->dy = 400 - rand() % 800;
		
		effect->dx /= 100;
		effect->dy /= 100;
		
		effect->texture = whiteSquare8;
		
		effect->color = b->color;
		
		effect->color.a = rand() % 255;
		
		effect->life = rand() % FPS;
	}
}
