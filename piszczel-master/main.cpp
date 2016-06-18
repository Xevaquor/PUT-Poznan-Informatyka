/*****************************************************************************
	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

	3. This notice may not be removed or altered from any source
	distribution.

	xevaquor@hotmail.com

*****************************************************************************/

#include <windows.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Pitch
{
	int frequency, duration;
	Pitch(int fq, int dr) : frequency(fq), duration(dr){}
	void Play()
	{
		if(frequency != 0)
			Beep(frequency, duration);
		else
			Sleep(duration);
	}
};

vector<Pitch> Melody;
int Repeats = 1;
int Delay = 0;

void MBox(const char* message)
{
	MessageBox(0, message, "OWH!",0);
}

void LoadMelody(const char* filename)
{
	ifstream input(filename);
	if(!input.is_open())
	{
		MBox("File not found!");
		exit(1);
	}

	input >> Repeats;
	input >> Delay;

	int freq, dur;
	while(!input.eof())
	{
		input >> dur;
		input >> freq;
		Melody.push_back(Pitch(freq, dur));
	}
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpszCommandLine, INT)
{
	std::string	melodyFileName = "music.txt";
	if(strlen(lpszCommandLine) > 0)
	{
		melodyFileName = lpszCommandLine;
		if(melodyFileName[0] == '"')
		{
			melodyFileName.erase(0,1);
			melodyFileName.erase(melodyFileName.size() - 1, 1);
		}
	}

	LoadMelody(melodyFileName.c_str());
	
	while(Repeats--)
	{
		for(int i = 0; i < Melody.size(); i++)
		{
			Melody[i].Play();
		}
		Sleep(Delay * 1000);
	}
	return 0;
}
