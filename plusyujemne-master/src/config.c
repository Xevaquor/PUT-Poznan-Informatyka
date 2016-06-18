#include "config.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Configuration g_GLobalConfiguration;

struct Configuration LoadConfigFile(const char *filename)
{
	assert(filename != NULL);
	struct Configuration xd;
	FILE *f = fopen(filename, "rt");
	char line[512] = {0};
	char name[512] = {0};
	char val[512] = {0};
	
	if (f == NULL)
	{
		fprintf(stderr, "Failed to open config file: %s\n", filename);
		exit(1);
	}

	while(fgets(line, 512, f) != NULL)
	{
		if(sscanf(line, "%[^=]= %s\n", name, val) == 2)
		{
			//really don't like those trailing spaces but looks like it's the easiest way
			if(strcmp("XResolution ", name)==0)
				xd.XResolution = atoi(val);
			else if (strcmp("YResolution ", name)==0)
				xd.YResolution = atoi(val);
			else if (strcmp("RocketSpeed ", name) == 0)
				xd.RocketSpeed = (float)atof(val);
			else if (strcmp("PlayerXVelocity ", name) == 0)
				xd.PlayerXVelocity = (float)atof(val);
			else if (strcmp("PlayerYVelocity ", name) == 0)
				xd.PlayerYVelocity = (float)atof(val);
			else if (strcmp("IdiotInterval ", name) == 0)
				xd.IdiotInterval = atoi(val);
			else if (strcmp("KamikadzeInterval ", name) == 0)
				xd.KamikadzeInterval = atoi(val);
			else if (strcmp("EnemyShootInterval ", name) == 0)
				xd.EnemyShootInterval = atoi(val);
			else if (strcmp("EnemyCrashDamage ", name) == 0)
				xd.EnemyCrashDamage = (float) atof(val);
			else if (strcmp("PlayerCrashDamage ", name) == 0)
				xd.PlayerCrashDamage = (float) atof(val);
			else if (strcmp("KamikadzeScore ", name) == 0)
				xd.KamikadzeScore = atoi(val);
			else if (strcmp("IdiotScore ", name) == 0)
				xd.IdiotScore = atoi(val);
			else if (strcmp("HP ", name) == 0)
				xd.HP = atoi(val);
			else
				fprintf(stderr, "Unknown config entry: %s\n", name);
		}
		else
		{
			fprintf(stderr, "Invalid line in config file: %s", line);
		}
	}
	fclose(f);
	return xd;
}
