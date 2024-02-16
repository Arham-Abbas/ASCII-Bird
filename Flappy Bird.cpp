#include <iostream>
#include <fstream>
#include <chrono>
#include <conio.h>
#include <Windows.h>
#include "Header.hpp"
bool g = false, q = false;
short p, r;
int  d = 1000;
long s = 0;
std::chrono::milliseconds m;
void gotoxy(short x, short y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x,y });
}
void clrscr()
{
    short i, j;
    for (j = 1; j < 29; j++)
    {
        gotoxy(1, j);
        for (i = 1; i < 119; i++)
            std::cout << " ";
    }
}
void death()
{
    long n;
    std::fstream f;
    gotoxy(55, 14);
    std::cout << "GAME OVER! "<<s;
    (void)_getch();
    gotoxy(55, 14);
    std::cout << "                                ";
    f.open(".GameData.dat", std::fstream::in | std::fstream::binary | std::fstream::_Nocreate);
    if (f.is_open())
    {
        f.read((char*)&n, sizeof(n));
        if (s < n)
            s = n;
        f.close();
    }
    f.open(".GameData.dat", std::fstream::out | std::fstream::binary);
    f.write((char*)&s, sizeof(s));
    f.write((char*)&d, sizeof(d));
    f.write((char*)&g, sizeof(g));
    f.close();
}
void drawWindow()
{
    short i;
    for (i = 0; i < 120; i++)
        std::cout << "=";
    for (i = 1; i < 29; i++)
    {
        gotoxy(0, i);
        std::cout << "|";
        gotoxy(119, i);
        std::cout << "|";
    }
    gotoxy(0, 29);
    for (i = 0; i < 120; i++)
        std::cout << "=";
}
int getInput()
{
    int i;
    std::chrono::milliseconds n;
    n = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    for (i = (int)m.count() - (int)n.count() + d; i > 0; i--)
    {
        if (_kbhit())
        {
            (void)_getch();
            if (_kbhit())
                (void)_getch();
            m = n;
            return 1;
        }
    }
    m = n;
    return 0;
}
void moveUp()
{
    gotoxy(10, p);
    std::cout << " ";
    p -=2;
    if (p <= 0)
        return;
    gotoxy(10, p);
    std::cout << "M";
}
void moveDown()
{
    gotoxy(10, p);
    std::cout << " ";
    p ++;
    if (p == 29)
        return;
    gotoxy(10, p);
    std::cout << "W";
}
class Pillar
{
private:
    short l[4];
    int  r[4], n;
    void removePillar(int w)
    {
        short i;
        for (i = 1; i < 29; i++)
        {
            gotoxy(1, i);
            std::cout << " ";
            gotoxy(6, i);
            std::cout << " ";
        }
        gotoxy(1, r[w]);
        std::cout << "     ";
        gotoxy(1, r[w] + 5);
        std::cout << "     ";
        l[w] = -1;
        s++;
        gotoxy(2, 2);
        std::cout << "SCORE: " << s;
    }
public:
    Pillar()
    {
        int i;
        for (i = 0; i < 4; i++)
        {
            l[i] = -1;
            r[i] = NULL;
        }
        n = NULL;
    }
    void drawPillar()
    {
        short i;
        r[n] = (rand() % 21) + 2;
        for (i = 1; i < 29; i++)
        {
            if ((i > r[n]) && (i < (r[n] + 5)))
                continue;
            gotoxy(113, i);
            std::cout << "|";
            gotoxy(118, i);
            std::cout << "|";
        }
        gotoxy(113, r[n]);
        std::cout << "=====";
        gotoxy(113, r[n] + 5);
        std::cout << "=====";
        l[n] = 113;
        if (n == 3)
            n = 0;
        else
        n++;
    }
    bool movePillar()
    {
        short i;
        int j;
        for (j = 0; j < 4; j++)
        {
            if (l[j] == 1)
            {
                removePillar(j);
                continue;
            }
            if (l[j] > 1)
                l[j]--;
            if ((l[j] >= 6 && l[j] <= 10) && !(p > r[j] && p < (r[j] + 5)))
                return false;
            for (i = 1; i < 29; i++)
            {
                if (l[j] != -1)
                {
                    if (i > r[j] && i < r[j] + 5)
                        continue;
                    if (i == r[j] || i == r[j] + 5)
                    {
                        gotoxy(l[j], i);
                        std::cout << "=";
                        gotoxy(l[j] + 6, i);
                        std::cout << " ";
                    }
                    else
                    {
                        gotoxy(l[j], i);
                        std::cout << "| ";
                        gotoxy(l[j] + 5, i);
                        std::cout << "| ";
                    }
                }
            }
            if ((l[j] >= 6 && l[j] <= 10) && !(p > r[j] && p < (r[j] + 5)))
                return false;
        }
        return true;
    }
    ~Pillar()
    {
        int i;
        for (i = 0; i < 4; i++)
        {
            l[i] = NULL;
            r[i] = NULL;
        }
        n = NULL;
    }
};
int main()
{
    int i;
    std::fstream f;
    srand((unsigned int)time(NULL));
    CONSOLE_SCREEN_BUFFER_INFO w;
    system("cls");
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &w);
    if (((w.srWindow.Right - w.srWindow.Left) != 119) || ((w.srWindow.Bottom - w.srWindow.Top) != 29))
    {
        std::cout << "Console Window is not set at the optimal size, you may experience some issues";
        (void)_getch();
        gotoxy(0, 0);
    }
    CONSOLE_CURSOR_INFO c;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
    c.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
    drawWindow();
    while (true)
    {
        Pillar o;
        f.open(".GameData.dat", std::fstream::in | std::fstream::binary | std::fstream::_Nocreate);
        if (f.is_open())
        {
            f.read((char*)&s, sizeof(s));
            f.read((char*)&d, sizeof(d));
            f.read((char*)&g, sizeof(g));
            f.close();
        }
        drawMenu();
        gotoxy(45, 14);
        std::cout << "Press any key to begin";
        (void)_getch();
        gotoxy(45, 14);
        for (i = 0; i < 23; i++)
            std::cout << " ";
        p = 14;
        gotoxy(10, 14);
        std::cout << "W";
        gotoxy(2, 2);
        s = 0;
        std::cout << "SCORE: " << s;
        m = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        i = 30;
        do
        {
            moveDown();
        l: if (p <= 0 || p >= 29)
            break;
        if (i == 30)
        {
            i = 0;
            o.drawPillar();
        }
        if (getInput())
        {
            moveUp();
            goto l;
        }
        i++;
        } while (o.movePillar());
        clrscr();
        death();
        o.~Pillar();
    }
    return 0;
}