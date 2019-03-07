#include <iostream>
#include <conio.h>
#include "functions.h"

using namespace std;

bool gameOver; // Indicates if the game have to stop or not.
const int width = 20; // Indicates the width of the game.
const int heigth = 20; // Indicates the height of the game.
int x;
int y;
int fruitX;
int fruitY;
int score;

enum eDirection {
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

eDirection dir; // Indicates the direction key of the snake.

void setUp()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = heigth / 2;
	randomFruit();
	score = 0;
}

void draw()
{
	// We gonna clear the console.
	// On Windows: system("cls") On linux: system("clear")
	system("cls");

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heigth; j++)
		{
			if (j == 0 or j == heigth - 1)
				cout << "#";

			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
				cout << " ";
        }
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout <<endl << "Score: " << score;
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;

		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
		default:
			break;
		}
	}
}

void logic()
{
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x >= width or x <= 0 or y >= heigth or y <= 0)
		gameOver = true;

	if (x == fruitX and y == fruitY)
	{
		score++;
		randomFruit();
	}
}

void randomFruit()
{
	fruitX = rand() % width;
	fruitY = rand() % heigth;
}

void core()
{
	setUp();
    while (!gameOver)
	{
		draw();
		input();
		logic();
		// We gonna sleep the frame for ten seconds.
		// In Windows: Sleep(10) on Linux: sleep(10).

	}
}

int main()
{
	core();
	return 0;
}

