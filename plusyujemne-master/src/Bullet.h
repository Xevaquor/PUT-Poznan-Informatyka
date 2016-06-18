#ifndef _ALLY_BULLET_
#define _ALLY_BULLET_

#include "AnimatedSprite.h"

struct Bullet
{
	struct AnimatedSprite as;
	/* prędkość pocisku (oś OY) */
	float Velocity;
	/* Czy jest "żywy" tj czy powinien być aktualizowany i rysowany */
	int IsAlive;
	/* Obrażenia jakie zada po uderzeniu */
	float Damage;
};

/* Tworzy standardowy pocisk gracza w podanym miejscu */
struct Bullet *CreateStandardBullet(struct Vector2 spawn);

/* Tworzy rakietę w podanym miejscu */
struct Bullet *CreateMissile(struct Vector2 spawn);

/* AKtualizuje pocisk (przesuwa go) */
void UpdateBullet(struct Bullet *b);

/* Tworzy pocisk przeciwnika klasy Idiot */
struct Bullet *CreateEnemyIdiotMissile(struct Vector2 spawn);

/* Tworzy pocisk przeciwnika klasy Kamiakdze */
struct Bullet *CreateEnemyKamikadzeMissile(struct Vector2 spawn);


#endif 
