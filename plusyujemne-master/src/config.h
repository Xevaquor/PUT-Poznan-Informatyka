#ifndef _CONFIG_H_
#define _CONFIG_H_

struct Configuration
{
	/* rozdzielczość ekranu */
	int XResolution, YResolution;
	/* Prędkość rakiety wystrzelonej przez gracza */
	float RocketSpeed;
	/* szybkość poruszania sie gracza */
	float PlayerXVelocity, PlayerYVelocity;
	/* cykle między spawnami wrogów */
	int IdiotInterval, KamikadzeInterval;
	/* cykle między strzałami wrogów */
	int EnemyShootInterval;
	/* obrażenia zadawane przy zderzeniu */
	float EnemyCrashDamage, PlayerCrashDamage;
	/* punkty za zabicie wrogów */
	int KamikadzeScore, IdiotScore;
	/* Początkowe punkty życia gracza */
	int HP;
};

/* Globalny obiekt trzymający konfigurację */
extern struct Configuration g_GLobalConfiguration;

/* Wczytywanie ustawień z pliku */
struct Configuration LoadConfigFile(const char *filename);

#endif
