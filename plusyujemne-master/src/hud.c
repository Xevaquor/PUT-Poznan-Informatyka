#include "hud.h"

#include <stdio.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include "config.h"
#include "util.h"

#define HP_BAR_HEIGHT 7
#define HP_BAR_RATIO 3.

static ALLEGRO_FONT *font;

void InitHUD(void)
{
	font = al_create_builtin_font();
}

void RenderHUD(int hp, int maxhp, int score, int TTR)
{
	al_draw_line(10, 10, 10 + maxhp * HP_BAR_RATIO, 10, al_map_rgb(127,0,0),
		HP_BAR_HEIGHT);
	al_draw_line(10, 10, 10 + hp * HP_BAR_RATIO, 10, al_map_rgb(255,0,0),
		HP_BAR_HEIGHT);

	char formatted[128];
	sprintf(formatted, "Score: %d points.", score);
	al_draw_text(font, al_map_rgb(255, 255, 255), 10, 20, 0,
	 formatted);
	sprintf(formatted, "Time To Rocket: %d", TTR);
	al_draw_text(font, al_map_rgb(255,255,255), 10,40,0,
		formatted);

}

void RenderGameOver(int score)
{
	al_clear_to_color(al_map_rgb(0x25, 0x25, 0x25));
	char buffer[128] = { 0 };
	sprintf(buffer, "You have scored %d points.", score);
	struct Vector2 center = GetScreenCenter();
	al_draw_text(font, al_map_rgb(255, 255, 255), center.x, center.y - 10, ALLEGRO_ALIGN_CENTER, "GAME OVER");
	al_draw_text(font, al_map_rgb(255, 255, 255), center.x, center.y + 10, ALLEGRO_ALIGN_CENTER, buffer);
}