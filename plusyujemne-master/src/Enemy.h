#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "AnimatedSprite.h"
#include "config.h"

/* rodzaj "sztucznej inteligencji" wroga */
enum ENEMY_AI {AI_IDIOT, AI_KAMIKADZE};

/* lista wrogów */
extern struct LinkedList *Enemies;
/* lista pocisków wystrzelonych przez wrogów */
extern struct LinkedList *Bullets;

struct Enemy
{
	struct AnimatedSprite Sprite;
	/* prędkość poruszania się */
	float YVelocity, XVelocity;
	/* cykle między oddaniem strzału */
	int ShootInterval;
	/* cykle do oddania następnego strzału */
	int TimeToShoot;
	/* rodzaj AI */
	enum ENEMY_AI Ai;
	/* pozostałe punkty życia */
	int HP;
};

/* zainicjuj moduł */
void InitEnemy(void);

/* zespawnuj wroga w losowym miejscu */
void SpawnEnemy(enum ENEMY_AI ai);

/* zaktualizuj stan wrogów (przesuń, strzel) */
void UpdateEnemies(int playerXPos);

/*narysuj wrogów */
void RenderEnemies(void);

/* zamknij moduł */
void CloseEnemy(void);

#endif
