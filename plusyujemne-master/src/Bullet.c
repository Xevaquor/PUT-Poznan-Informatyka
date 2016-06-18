#include "Bullet.h"
#include "ImageManager.h"
#include "AnimatedSprite.h"
#include "config.h"

struct Bullet *CreateStandardBullet(struct Vector2 spawn)
{
	struct Bullet *b = malloc(sizeof(struct Bullet));
	b->as = CreateAnimatedSprite(spawn, ImageMan.StandardBullet, 4, 1);
	b->Damage = 20;
	b->IsAlive = 1;
	b->Velocity = 10;

	return b;
}

struct Bullet *CreateMissile(struct Vector2 spawn)
{
	struct Bullet *b = malloc(sizeof(struct Bullet));
	b->as = CreateAnimatedSprite(spawn, ImageMan.MissileBullet, 2, 10);
	b->Damage = 100;
	b->IsAlive = 1;
	b->Velocity = 11;

	return b;
}
struct Bullet *CreateEnemyIdiotMissile(struct Vector2 spawn)
{
	struct Bullet *b = malloc(sizeof(struct Bullet));
	b->as = CreateAnimatedSprite(spawn, ImageMan.IdiotMissile, 4, 10);
	b->Damage = 1;
	b->IsAlive = 1;
	b->Velocity = -11;

	return b;
}

struct Bullet *CreateEnemyKamikadzeMissile(struct Vector2 spawn)
{
	struct Bullet *b = malloc(sizeof(struct Bullet));
	b->as = CreateAnimatedSprite(spawn, ImageMan.KamikadzeMissile, 4, 10);
	b->Damage = 5;
	b->IsAlive = 1;
	b->Velocity = -17;

	return b;
}


void UpdateBullet(struct Bullet *b)
{
	if (b->as.Positon.y + b->as.YFrameSize < 0)
		b->IsAlive = 0;
	else if (b->as.Positon.y > g_GLobalConfiguration.YResolution)
		b->IsAlive = 0;

	UpdateAS(&b->as, 1);
	b->as.Positon.y -= b->Velocity;

}
