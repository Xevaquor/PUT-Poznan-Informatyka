#include "util.h"

#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\bitmap.h>
#include <stdio.h>

#include "init.h"
#include "ImageManager.h"

ALLEGRO_BITMAP *LoadImageFile(const char *filename)
{
	ALLEGRO_BITMAP *bmp = al_load_bitmap(filename);
	if (bmp == NULL)
	{
		fprintf(stderr, "Failed to load image: %s", filename);
		exit(1);
	}
	return bmp;

}

struct Vector2 GetScreenCenter(void)
{
	struct Vector2 center;
	center.x = g_GLobalConfiguration.XResolution / 2;
	center.y = g_GLobalConfiguration.YResolution / 2;

	return center;

}
ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h)
{
	ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;

	resized_bmp = al_create_bitmap(w, h);
	if (!resized_bmp) return NULL;

	loaded_bmp = al_load_bitmap(filename);
	if (!loaded_bmp)
	{
		al_destroy_bitmap(resized_bmp);
		return NULL;
	}

	prev_target = al_get_target_bitmap();
	al_set_target_bitmap(resized_bmp);
	al_draw_scaled_bitmap(loaded_bmp,
		0, 0,                                
		al_get_bitmap_width(loaded_bmp),     
		al_get_bitmap_height(loaded_bmp),    
		0, 0,                                
		w, h,                                
		0                                    
		);

	al_set_target_bitmap(prev_target);
	al_destroy_bitmap(loaded_bmp);

	return resized_bmp;
}