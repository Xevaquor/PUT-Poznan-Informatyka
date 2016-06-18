#ifndef _UTIL_H_
#define _UTIL_H_

#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

struct Vector2
{
	float x;
	float y;
};

//załaduj bitmapę
ALLEGRO_BITMAP *LoadImageFile(const char *filename);
//załaduj bitmapę i przeskaluj ją do rozmiaru
ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h);

//pobierz środek ekranu
struct Vector2 GetScreenCenter(void);

#endif
