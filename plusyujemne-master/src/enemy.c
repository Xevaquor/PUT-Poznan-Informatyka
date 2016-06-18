#include "Enemy.h"

#include "util.h"
#include "config.h"
#include "Bullet.h"
#include "LinkedList.h"
#include "ImageManager.h"

struct LinkedList *Enemies;
struct LinkedList *Bullets;

void ManageSpawn(void);

void InitEnemy(void)
{
	Enemies = CreateLinkedList();
	Bullets = CreateLinkedList();
}

void CloseEnemy(void)
{
	ReleaseLinkedList(Enemies, true);
	free(Enemies);
	ReleaseLinkedList(Bullets, true);
	free(Bullets);
}

struct Enemy *CreateIdiotEnemy(void)
{
	struct Enemy *e = malloc(sizeof(struct Enemy));
	e->Sprite = CreateAnimatedSprite(GetScreenCenter(), ImageMan.Enemy, 3, 5);
	e->ShootInterval = g_GLobalConfiguration.EnemyShootInterval;
	e->Ai = AI_IDIOT;
	e->TimeToShoot = 0;
	e->XVelocity = 0;
	e->YVelocity = 8;
	e->HP = 100;

	return e;
}

struct Enemy *CreateKamikadzeEnemy(void)
{
	struct Enemy *e = malloc(sizeof(struct Enemy));
	e->Sprite = CreateAnimatedSprite(GetScreenCenter(), ImageMan.Enemy, 3, 5);
	e->ShootInterval = g_GLobalConfiguration.EnemyShootInterval;
	e->Ai = AI_KAMIKADZE;
	e->TimeToShoot = 0;
	e->XVelocity = 4;
	e->YVelocity = 10;
	e->HP = 50;

	return e;
}

void EnemyShoot(struct Enemy *e)
{
	e->TimeToShoot = e->ShootInterval;
	struct Vector2 pos;
	struct Bullet *b;
	if (e->Ai == AI_IDIOT)
		b = CreateEnemyIdiotMissile(e->Sprite.Positon);
	else
		b = CreateEnemyKamikadzeMissile(e->Sprite.Positon);
	pos.x = e->Sprite.Positon.x + e->Sprite.XFrameSize / 2 - b->as.XFrameSize / 2;
	pos.y = e->Sprite.Positon.y;
	b->as.Positon = pos;
	PrependLL(Bullets, b);

}

void UpdateBullets(void)
{
	struct LinkedListNode *iter = Bullets->head;
	struct LinkedList *toDelete = CreateLinkedList();
	while (iter != NULL)
	{
		UpdateBullet(iter->val);
		struct Bullet *b = iter->val;
		if (!b->IsAlive)
			PrependLL(toDelete, iter->val);
		iter = iter->next;
	}
	iter = toDelete->head;
	while (iter != NULL)
	{
		RemoveLL(Bullets, iter->val);
		iter = iter->next;
	}
	ReleaseLinkedList(toDelete, 0);
}

void UpdateEnemies(int playerXPos)
{
	assert(Enemies != NULL);
	struct LinkedListNode *iter = Enemies->head;
	struct LinkedList *toDelete = CreateLinkedList();
	while (iter != NULL)
	{
		struct Enemy*e = iter->val;

		if (e->Sprite.Positon.y > g_GLobalConfiguration.YResolution
			|| e->HP <= 0)
			PrependLL(toDelete, iter->val);
		UpdateAS(&e->Sprite, 1);

		if (e->Ai == AI_IDIOT)
		{
			e->Sprite.Positon.y += e->YVelocity;
		}
		else if (e->Ai == AI_KAMIKADZE)
		{
			e->Sprite.Positon.y += e->YVelocity;
			float xmove = playerXPos - e->Sprite.Positon.x;
			if (xmove > 0)
				xmove = min(e->XVelocity, xmove);
			else
				xmove = max(-e->XVelocity, xmove);
			e->Sprite.Positon.x += xmove;
		}
		else
		{
			assert(false);
		}

		if (e->TimeToShoot-- <= 0)
		{
			EnemyShoot(e);
		}

		iter = iter->next;
	}

	iter = toDelete->head;
	while (iter != NULL)
	{
		RemoveLL(Enemies, iter->val);
		iter = iter->next;
	}
	ReleaseLinkedList(toDelete, 0);

	UpdateBullets();

	ManageSpawn();
}

void RenderEnemies(void)
{
	assert(Enemies != NULL);
	struct LinkedListNode *iter = Enemies->head;
	while (iter != NULL)
	{
		struct Enemy*e = iter->val;
		DrawAS(&e->Sprite);

		iter = iter->next;
	}

	assert(Bullets != NULL);
	iter = Bullets->head;
	while (iter != NULL)
	{
		struct Bullet *b = iter->val;
		DrawAS(&b->as);

		iter = iter->next;
	}
}

void SpawnEnemy(enum ENEMY_AI ai)
{
	if (ai == AI_IDIOT)
	{
		struct Enemy *e = CreateIdiotEnemy();
		e->Sprite.Positon.y = - ((int) e->Sprite.YFrameSize);
		e->Sprite.Positon.x = rand() % (g_GLobalConfiguration.XResolution - e->Sprite.XFrameSize);
		PrependLL(Enemies, e);
	}
	else if (ai == AI_KAMIKADZE)
	{
		struct Enemy *e = CreateKamikadzeEnemy();
		e->Sprite.Positon.y = -((int)e->Sprite.YFrameSize);
		e->Sprite.Positon.x = rand() % (g_GLobalConfiguration.XResolution - e->Sprite.XFrameSize);
		PrependLL(Enemies, e);
	}
	else
	{
		assert(false);
	}
}


void ManageSpawn(void)
{
	static int ticksFromLastSpawnIdiot = 10;
	if (ticksFromLastSpawnIdiot++ >= g_GLobalConfiguration.IdiotInterval)
	{
		ticksFromLastSpawnIdiot -= g_GLobalConfiguration.IdiotInterval;
		SpawnEnemy(AI_IDIOT);
	}
	static int ticksFromLastSpawnKamikadze = 10;
	if (ticksFromLastSpawnKamikadze++ >= g_GLobalConfiguration.KamikadzeInterval)
	{
		ticksFromLastSpawnKamikadze -= g_GLobalConfiguration.KamikadzeInterval;
		SpawnEnemy(AI_KAMIKADZE);
	}

}


