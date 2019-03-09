#include <iostream>
#include <conio.h>
#include <Windows.h>
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
int tailX[100];
int tailY[100];
int tailLength;

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
			{
				bool ableToPrint = false;
				for (int iterator = 0; iterator < tailLength; iterator++)
				{
					if (tailX[iterator] == j and tailY[iterator] == i)
					{
						cout << "o";
						ableToPrint = true;
					}
				}

				if (!ableToPrint)
					cout << " ";
			}
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
	int previousX = tailX[0];
	int previousY = tailY[0];
	int auxPreviousX;
	int auxPreviousY;
	tailX[0] = x;
	tailY[0] = y;

	for (int iterator = 1; iterator < tailLength; iterator++)
	{
		auxPreviousX = tailX[iterator];
		auxPreviousY = tailY[iterator];
		tailX[iterator] = previousX;
		tailY[iterator] = previousY;
		previousX = auxPreviousX;
		previousY = auxPreviousY;
	}

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

	// ! We can add two game moods.

	// You can crash with the walls.
	/*
	* if (x > width or x < 0 or y > heigth or y < 0)
	*  	 gameOver = true;
	*/
	// You can trough the walls.
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= width) y = 0; else if (y < 0) y = heigth - 1;


	for (int iterator = 0; iterator < tailLength; iterator++)
		if (tailX[iterator] == x && tailY[iterator] == y)
			gameOver == true;


	if (x == fruitX and y == fruitY)
	{
		score++;
		randomFruit();
		tailLength++;
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
		Sleep(100);
	}
}

int main()
{
	core();
	return 0;
}
