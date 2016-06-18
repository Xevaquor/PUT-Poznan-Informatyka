#include "input.h"
#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

static ALLEGRO_KEYBOARD_STATE KeyboardState;
static ALLEGRO_MOUSE_STATE MouseState;

void UpdateInput(void)
{
	al_get_mouse_state(&MouseState);
	al_get_keyboard_state(&KeyboardState);
}
int IsKeyPressed(int keyCode)
{
	return al_key_down(&KeyboardState, keyCode);
}




