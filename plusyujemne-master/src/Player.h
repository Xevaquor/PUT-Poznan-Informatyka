#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "AnimatedSprite.h"
#include "LinkedList.h"

struct Player
{
	struct AnimatedSprite Sprite;
	float YVelocity, XVelocity;
	struct LinkedList *Bullets;
	int StandardShootInterval;
	int TimeToStandardShoot;
	int MissileShootInterval;
	int TimeToMissileShoot;
	int HP;
	int MaxHP;
	int Score;
};

//utwórz gracza
struct Player CreatePlayer(void);

//ruch z pilnowaniem aby nie wylecieć za okno
void MoveLeft(struct Player *p);
void MoveRight(struct Player *p);
void MoveUp(struct Player *p);
void MoveDown(struct Player *p);

//wystrzel pociski
void ShootStandard(struct Player *p);
void ShootMissile(struct Player *p);

//zaktualizuj stan gracza
void UpdatePlayer(struct Player *p);

//sprawdź kolizje z pociskam wrogów
void CheckEnemyBullets(struct Player *p);
//sprawdź czy pociski gracza nie uderzyły w kogoś
void CheckPlayerBullets(struct Player *p);


#endif
