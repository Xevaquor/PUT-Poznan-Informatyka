#ifndef _HUD_H_
#define _HUD_H_

/* zainicjuj moduł */
void InitHUD(void);

/* narysuj hud - pkt życia gracza, max pkt życia, wynik punktowy, czas
 * do możliwośći wystrzelenia kolejnej rakiety */
void RenderHUD(int hp, int maxhp, int score, int TTR);

/* rysuj koniec gry */
void RenderGameOver(int score);
#endif

