#include "AnimatedSprite.h"
#include <assert.h>


struct AnimatedSprite CreateAnimatedSprite(struct Vector2 pos, ALLEGRO_BITMAP *bmp,
	size_t frameCount, size_t frameTime)
{
	assert(bmp != NULL);
	struct AnimatedSprite as;
	as.Bitmap = bmp;
	as.FrameTicks = frameTime;
	as.Positon = pos;
	as.TickElapsed = 0;
	as.XFrame = 0;
	as.XFrames = frameCount;
	as.XFrameSize = al_get_bitmap_width(bmp) / as.XFrames;
	as.YFrameSize = al_get_bitmap_height(bmp);

	return as;
}

void UpdateAS(struct AnimatedSprite *as, int ticks)
{
	as->TickElapsed += ticks;
	if (as->TickElapsed >= as->FrameTicks)
	{
		as->TickElapsed -= as->FrameTicks;
		as->XFrame = (as->XFrame + 1) % as->XFrames;
	}
}

void DrawAS(struct AnimatedSprite *as)
{
	al_draw_bitmap_region(as->Bitmap, as->XFrame * as->XFrameSize, 0,
		as->XFrameSize, as->YFrameSize, as->Positon.x, as->Positon.y, 0);

}



int Intersects(struct AnimatedSprite *a, struct AnimatedSprite *b)
{
	return
		a->Positon.x < b->Positon.x + b->XFrameSize &&
		b->Positon.x < a->Positon.x + a->XFrameSize &&
		a->Positon.y < b->Positon.y + b->YFrameSize &&
		b->Positon.y < a->Positon.y + a->YFrameSize;
}
