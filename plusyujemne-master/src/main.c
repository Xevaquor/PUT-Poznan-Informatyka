
#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\display.h>

#include <stdio.h>
#include "LinkedList.h"
#include "input.h"
#include "init.h"
#include "util.h"
#include "config.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "Bullet.h"
#include "Background.h"
#include "hud.h"
#include "Enemy.h"

struct Player player;

enum GAME_STATE {GS_PLAY, GS_END};

enum GAME_STATE GameState = GS_PLAY;

void GameLogic(void)
{
	if (IsKeyPressed(ALLEGRO_KEY_LEFT))
		MoveLeft(&player);
	if (IsKeyPressed(ALLEGRO_KEY_RIGHT))
		MoveRight(&player);
	if (IsKeyPressed(ALLEGRO_KEY_UP))
		MoveUp(&player);
	if (IsKeyPressed(ALLEGRO_KEY_DOWN))
		MoveDown(&player);

	if (IsKeyPressed(ALLEGRO_KEY_SPACE))
		ShootStandard(&player);

	if (IsKeyPressed(ALLEGRO_KEY_LCTRL))
		ShootMissile(&player);

	if (IsKeyPressed(ALLEGRO_KEY_LSHIFT))
		SpawnEnemy(AI_IDIOT);

	CheckEnemyBullets(&player);
	CheckPlayerBullets(&player);
	UpdatePlayer(&player);
	UpdateEnemies(player.Sprite.Positon.x);
	UpdateBackground();

	if(player.HP <= 0)
		GameState = GS_END;

}

void DoLogic(void)
{
	if(GameState == GS_PLAY)
		GameLogic();
}
void RenderGame(void)
{	
	RenderBackground();

	struct LinkedListNode *iter = player.Bullets->head;
	while (iter != NULL)
	{
		struct Bullet *b = (struct Bullet*) iter->val;
		DrawAS(&b->as);
		iter = iter->next;
	}

	DrawAS(&player.Sprite);
	RenderEnemies();

	RenderHUD(player.HP, player.MaxHP, player.Score,
		player.TimeToMissileShoot);
}
void Render(void)
{
	if(GameState == GS_PLAY)
		RenderGame();
	else
	{
		RenderGameOver(player.Score);
	}
}

int main()
{
	ALLEGRO_DISPLAY *display = NULL;

	init(&display);

	
	struct Vector2 zero;
	zero.x = zero.y = 0;
	player = CreatePlayer();

	



	double dt = 0.0;
	double lastUpdateTime = al_current_time();
	double accumulator = 0;
	double TIME_STEP = 1. / 30;



	UpdateInput();
	int isRunning = 1;
	while (isRunning)
	{
		dt = al_current_time() - lastUpdateTime;
		lastUpdateTime += dt;
		accumulator += dt;

		UpdateInput();

		if (IsKeyPressed(ALLEGRO_KEY_ESCAPE))
			break;

		while (accumulator > TIME_STEP)
		{
			DoLogic();

			accumulator -= TIME_STEP;
		}
		Render();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0x77, 0, 255));
	}

	al_destroy_display(display);
	CloseEnemy();

	return 0;
}
