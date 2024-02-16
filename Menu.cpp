#include <iostream>
#include <thread>
#include <conio.h>
#include <Windows.h>
#include "Header.hpp"
std::thread t;
void options()
{
	bool a;
	char c;
	short y;
l:clrscr();
	a = false;
	gotoxy(2, 2);
	std::cout << "ESC";
	gotoxy(113, 2);
	std::cout << "ENTER";
	gotoxy(45, 13);
	std::cout << "> Difficulty: ";
	switch (d)
	{
	case 1000: std::cout << "Easy";
		break;
	case 900: std::cout << "Medium";
		break;
	case 800: std::cout << "Hard";
		break;
	default: clrscr();
		gotoxy(2, 2);
		std::cout << "An error has occurred while trying to display difficulty. Please report this issue.";
		d = 1000;
		(void)_getch();
		clrscr();
		return;
	}
	gotoxy(45, 15);
	std::cout << "Music: ";
	if (g)
		std::cout << "ON";
	else
		std::cout << "OFF";
	l2:while ((c = _getch()) != 27)
	{
		if (c == '\r')
		{
			if (a)
			{
				gotoxy(54, 15);
				if (g)
				{
					g = false;
					std::cout << "OFF";
				}
				else
				{
					g = true;
					std::cout << "ON ";
				}
			if (g && !q)
				t = std::thread(sound);
			else if (!g && q)
				t.join();
			goto l2;
			}
			gotoxy(45, 13);
			std::cout << "Difficulty: > ";
			switch (d)
			{
			case 1000: y = 13;
				break;
			case 900: y = 11;
				break;
			case 800: y = 9;
				break;
			default: goto l;
			}
			gotoxy(59, y);
			std::cout << "Easy";
			gotoxy(59, y + 2);
			std::cout << "Medium";
			gotoxy(59, y + 4);
			std::cout << "Hard";
			while (true)
			{
			l3:c = _getch();
				if (c == '\r')
					goto l;
				if (_kbhit())
				{
					c = _getch();
					if (c == 72)
					{
						switch (d)
						{
						case 900: y = 11;
							break;
						case 800: y = 9;
							break;
						default: goto l3;
						}
						d+=100;
						gotoxy(59, y);
						std::cout << "    ";
						gotoxy(59, y + 2);
						std::cout << "Easy  ";
						gotoxy(59, y + 4);
						std::cout << "Medium";
						gotoxy(59, y + 6);
						std::cout << "Hard";
					}
					else if (c == 80)
					{
						switch (d)
						{
						case 1000: y = 11;
							break;
						case 900: y = 9;
							break;
						default: goto l3;
						}
						d-=100;
						gotoxy(59, y);
						std::cout << "Easy";
						gotoxy(59, y + 2);
						std::cout << "Medium";
						gotoxy(59, y + 4);
						std::cout << "Hard  ";
						gotoxy(59, y + 6);
						std::cout << "    ";
					}
				}
			}
		}
		else if (_kbhit())
		{
			c = _getch();
			if (c == 80 && !a)
			{
				gotoxy(45, 13);
				std::cout << "Difficulty: ";
				switch (d)
				{
				case 1000: std::cout << "Easy  ";
					break;
				case 900: std::cout << "Medium  ";
					break;
				case 800: std::cout << "Hard  ";
					break;
				default: clrscr();
					gotoxy(2, 2);
					std::cout << "An error has occurred while trying to display difficulty. Please report this issue.";
					d = 1000;
					(void)_getch();
					clrscr();
					return;
				}
				gotoxy(45, 15);
				std::cout << "> Music: ";
				if (g)
					std::cout << "ON";
				else
					std::cout << "OFF";
				a = true;
			}
			else if (c == 72 && a)
			{
				gotoxy(45, 13);
				std::cout << "> Difficulty: ";
				switch (d)
				{
				case 1000: std::cout << "Easy";
					break;
				case 900: std::cout << "Medium";
					break;
				case 800: std::cout << "Hard";
					break;
				default: clrscr();
					gotoxy(2, 2);
					std::cout << "An error has occurred while trying to display difficulty. Please report this issue.";
					d = 1000;
					(void)_getch();
					clrscr();
					return;
				}
				gotoxy(45, 15);
				std::cout << "Music: ";
				if (g)
					std::cout << "ON  ";
				else
					std::cout << "OFF  ";
				a = false;
			}
		}
	}
}
void help()
{
	clrscr();
	gotoxy(2, 1);
	std::cout << "Tips & Controls\n\n| Press any key on the keyboard to move the bird UP. Bird constantly falls DOWN, keep counter-acting to pass through\n| the pipes.\n\n| If you are experiencing lag INCREASING the difficulty might help.\n\n| This app is not capable of handling different console window size, so DO NOT change the size of the console window.\n\n| The music in this game is encoded in .wav format which is a limitation for the function that I am using. Since .wav\n| is uncompressed the file size is increased exponentially (A 4MB .mp3 was converted to a 127MB .wav). This is the\n| reason for degraded audio quality, since I had to manually downmix audio to make it of reasonable size. But don't\n| fret! This app can play your music in the background too! You will see a SongList.txt file in the same folder as this|| app is, just open it with a text editor and write the proper (No extra spaces or next-line/ return-carriage character|| please) name of your file. You must use .wav audio file and the file must be present in the same folder as this app\n| is.\n\n| Press ANY KEY to go back.";
	(void)_getch();
}
void confirm()
{
	bool y = false;
	int c;
	clrscr();
	gotoxy(45, 14);
	std::cout << "Are you sure?";
	gotoxy(45, 15);
	std::cout << "YES    >  NO";
	while (true)
	{
		c = (int)_getch();
		if (c == '\r')
		{
			if (y)
			{
				if (q)
				{
					g = false;
					t.join();
				}
				exit(0);
			}
			else
				return;
		}
		if (_kbhit())
		{
			c = (int)_getch();
			if (c == 75 || c == 77)
			{
				gotoxy(45, 15);
				if (y)
				{
					std::cout << "YES    >  NO";
					y = false;
				}
				else
				{
					std::cout << ">  YES    NO";
					y = true;
				}
			}
		}
	}
}
int moveArrow(int a, int m)
{
	if (m == 72)
	{
		switch (a)
		{
		case 1:	a--;
			gotoxy(55, 12);
			std::cout << "> Start Game";
			gotoxy(55, 14);
			std::cout << "Options  ";
			return a;
		case 2: a--;
			gotoxy(55, 14);
			std::cout << "> Options";
			gotoxy(55, 16);
			std::cout << "Help  ";
			return a;
		case 3: a--;
			gotoxy(55, 16);
			std::cout << "> Help";
			gotoxy(55, 18);
			std::cout << "Exit  ";
			return a;
		default: return a;
		}
	}
	else if (m == 80)
	{
		switch (a)
		{
		case 0: a++;
			gotoxy(55, 12);
			std::cout << "Start Game  ";
			gotoxy(55, 14);
			std::cout << "> Options";
			return a;
		case 1: a++;
			gotoxy(55, 14);
			std::cout << "Options  ";
			gotoxy(55, 16);
			std::cout << "> Help";
			return a;
		case 2: a++;
			gotoxy(55, 16);
			std::cout << "Help  ";
			gotoxy(55, 18);
			std::cout << "> Exit";
			return a;
		}
	}
	return a;
}
void drawMenu()
{
	int a;
	char c;
	if (g && !q)
		t = std::thread(sound);
	while (true)
	{
		a = 0;
		gotoxy(2, 2);
		std::cout << "HIGH SCORE: " << s;
		gotoxy(55, 10);
		std::cout << "MAIN MENU";
		gotoxy(55, 12);
		std::cout << "> Start Game";
		gotoxy(55, 14);
		std::cout << "Options";
		gotoxy(55, 16);
		std::cout << "Help";
		gotoxy(55, 18);
		std::cout << "Exit";
		gotoxy(75, 11);
		std::cout << "^";
		gotoxy(75, 19);
		std::cout << "v";
		while (true)
		{
			c = _getch();
			if (_kbhit())
				a = moveArrow(a, (int)_getch());
			else if (c == '\r')
				break;
		}
		switch (a)
		{
		case 0: clrscr();
			return;
		case 1: options();
			break;
		case 2: help();
			break;
		case 3: confirm();
			break;
		}
		clrscr();
	}
}