#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <Windows.h>
#include "Header.hpp"
void sound()
{
	q = true;
	char c;
	int i, n = 1, r;
	std::string s;
	std::fstream f;
	std::wstring w;
	srand((unsigned int)time(NULL));
	f.open("SongList.txt", std::fstream::in | std::fstream::_Nocreate);
	if (f.is_open())
	{
		if (f.eof())
			return;
		else
			while (f.read(&c, sizeof(c)))
			{
				if (c == '\n')
					n++;
				if (f.eof())
				{
					n++;
					break;
				}
			}
		f.close();
	}
	else
		return;
l:f.open("SongList.txt", std::fstream::in | std::fstream::_Nocreate);
		r = rand() % n;
		i = NULL;
		s = "\0";
		if (f.is_open())
		{
			while (f.read(&c, sizeof(c)))
			{
				if (c == '\n')
					i++;
				else if (i == r)
					s = s + c;
				if (f.eof() || i == r + 1)
					break;
			}
			f.close();
		}
		else
			return;
		f.open(s, std::fstream::in | std::fstream::_Nocreate);
		if (f.is_open())
		{
			f.close();
			w = std::wstring(s.begin(), s.end());
			while(!(PlaySoundW(w.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT | SND_NOSTOP))&&g);
		}
		else
			return;
		if(g)
		goto l;
		PlaySoundW(NULL, 0, 0);
		q = false;
		return;
}