#include "entities.h"

static void touchOthers(void);
//handling entities (things they can do)
void doEntities(void)
{
	Entity *entity, *prev;
	
	prev = &arena.entityHead;
	
	for (entity = arena.entityHead.next ; entity != NULL ; entity = entity->next)
	{
		self = entity;
		
		if (entity->type)
		{
			entity->type();
		}
		//moving by adding dy and dx to y and x
		if (arena.type != THIRD || entity == player) {
			entity->x += entity->dx;
			entity->y += entity->dy;
		}
		
		if (entity->touch)
		{
			touchOthers();
		}
		
		entity->reload = MAX(entity->reload - 1, 0);
		
		//check if entity is a player so he can't go outside the screen
		if (entity == player)
		{
			entity->y = MIN(MAX(entity->y, entity->h / 2), ARENA_HEIGHT - entity->h / 2);
			entity->x = MIN(MAX(entity->x, entity->w / 2), ARENA_WIDTH - entity->w / 2);
		}
		//if entity's health goes to 0 or below we destroy it
		if (entity->health <= 0)
		{
			if (entity->die)
			{
				entity->die();
			}
			
			if (entity == arena.entityTail)
			{
				arena.entityTail = prev;
			}
			
			prev->next = entity->next;
			free(entity);
			entity = prev;
		}
		
		prev = entity;
	}
}
//iterate over every entity and check if it touches other entity
static void touchOthers(void)
{
	Entity *entity;
	int distance;
	for (entity = arena.entityHead.next ; entity != NULL ; entity = entity->next)
	{
		if (entity != self)
		{
			distance = getDistance(self->x, self->y, entity->x, entity->y);
			
			if (distance < entity->radius + self->radius)
			{
				self->touch(entity);
			}
		}
	}
}
//drawing entities
void drawEntities(void)
{
	Entity *entity;
	
	for (entity = arena.entityHead.next ; entity != NULL ; entity = entity->next)
	{
		SDL_SetTextureColorMod(entity->texture, entity->color.r, entity->color.g, entity->color.b);
		
		bitblitRotated(entity->texture, entity->x - arena.camera.x, entity->y - arena.camera.y, entity->angle);
	}
}
