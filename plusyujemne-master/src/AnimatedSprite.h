#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_

#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include <stddef.h>
#include "util.h"

/* Struktura animowanego sprite'a */
struct AnimatedSprite
{
	struct Vector2 Positon;
	ALLEGRO_BITMAP *Bitmap;
	/* ilość klatek */
	size_t XFrames;	
	/* aktualna klatka */				
	size_t XFrame;		
	/* cykle od ostatnie zmiany klatki */			
	int TickElapsed;
	/* cykle na klatkę */				
	int FrameTicks;
	/* rozmiar klatki */
	size_t XFrameSize, YFrameSize;
};

/* Tworzy AS na z określoną lokalizacją (pos),bitmapą (bmp),
 * zawierającego frameCount klatek, z których każda trwa frameTime cylki
 */
struct AnimatedSprite CreateAnimatedSprite(struct Vector2 pos, 
ALLEGRO_BITMAP *bmp, size_t frameCount, size_t frameTime);

/* Aktualizuje AS o ticks cykli */
void UpdateAS(struct AnimatedSprite *as, int ticks);
/* Rysuje AS na ekranie */
void DrawAS(struct AnimatedSprite *as);
/* Spawdza czy zachozi kolizja między dwoma ASami */
int Intersects(struct AnimatedSprite *a, struct AnimatedSprite *b);

#endif
