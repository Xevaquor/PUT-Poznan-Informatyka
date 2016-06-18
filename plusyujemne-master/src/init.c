#include "init.h"

#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include "config.h"
#include "ImageManager.h"
#include "hud.h"
#include "Enemy.h"

void init(ALLEGRO_DISPLAY **disp)
{
	al_init();
	al_install_keyboard();
	al_init_font_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_mouse();
	g_GLobalConfiguration = LoadConfigFile("xd");
	*disp = al_create_display(g_GLobalConfiguration.XResolution,
		g_GLobalConfiguration.YResolution);


	LoadImages();
	InitHUD();
	InitEnemy();

}
