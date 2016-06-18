#include "ImageManager.h"
#include "util.h"
#include "config.h"

struct ImageManager ImageMan;

void LoadImages(void)
{
	ImageMan.StandardBullet = LoadImageFile("gfx/bullet.png");
	ImageMan.MissileBullet = LoadImageFile("gfx/missile.png");
	ImageMan.Enemy = LoadImageFile("gfx/enemy.png");
	ImageMan.IdiotMissile = LoadImageFile("gfx/bullet_green.png");
	ImageMan.KamikadzeMissile = LoadImageFile("gfx/bullet_purple.png");
	ImageMan.Background = load_bitmap_at_size("gfx/background.png", g_GLobalConfiguration.XResolution,
		g_GLobalConfiguration.YResolution);
	//ImageMan.Background = LoadImageFile("gfx/background.png");
}