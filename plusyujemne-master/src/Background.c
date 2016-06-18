#include "Background.h"
#include "util.h"
#include "ImageManager.h"
#include "config.h"

static float YOffset = 0;

void UpdateBackground(void)
{
	YOffset += 2;
	if (YOffset > g_GLobalConfiguration.YResolution)
		YOffset -= g_GLobalConfiguration.YResolution;
}

void RenderBackground(void)
{
	al_draw_bitmap(ImageMan.Background, 0, YOffset, 0);
	al_draw_bitmap(ImageMan.Background, 0, YOffset-g_GLobalConfiguration.YResolution, 0);
}

