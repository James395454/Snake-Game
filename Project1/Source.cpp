#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <fstream>
using namespace std;
const int n = 20, m = 40;
void clearscreen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
struct piece
{
	int x, y;
};
void displaymap(char map[n][m])
{
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < m;j++)
			cout << map[i][j];
		cout << endl;
	}
}
void movesnake(char map[n][m], piece *snake, string move, int & size, piece & foodloc, bool & eat, int & score, string & previousmove, bool & gameover, int scoreadder)
{
	piece head;
	head.x = snake[size - 1].x; head.y = snake[size - 1].y;

	if (move == "up")
	{
		if (snake[size - 1].x - 1 != 0)
			--snake[size - 1].x;
		else
		{
			map[n - 2][snake[size - 1].y] = char(30);
			snake[size - 1].x = n - 2;
		}
	}

	else if (move == "down")
	{
		if ((snake[size - 1].x + 1 != n - 1))
			++snake[size - 1].x;
		else
		{
			map[1][snake[size - 1].y] = char(31);
			snake[size - 1].x = 1;
		}

	}
	else if (move == "right")
	{
		if (snake[size - 1].y + 1 != m - 1)
			++snake[size - 1].y;
		else
		{
			map[snake[size - 1].x][1] = char(16);
			snake[size - 1].y = 1;
		}

	}
	else if (move == "left")
	{
		if (snake[size - 1].y - 1 != 0)
			--snake[size - 1].y;
		else
		{
			map[snake[size - 1].x][m - 2] = char(17);
			snake[size - 1].y = m - 2;
		}
	}
	for (int i = 0;i < size - 1;i++)
		if ((snake[size - 1].x == snake[i].x) && (snake[size - 1].y == snake[i].y))
		gameover = true;

	if ((snake[size - 1].x != foodloc.x) || (snake[size - 1].y != foodloc.y))

	{
		map[snake[0].x][snake[0].y] = ' ';

		for (int i = 0;i < size - 2;i++)
		{
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[size - 2].x = head.x;snake[size - 2].y = head.y;

	}
	else if ((snake[size - 1].x == foodloc.x) && (snake[size - 1].y == foodloc.y))
	{

		snake[size].x = snake[size - 1].x;snake[size].y = snake[size - 1].y;
		snake[size - 1].x = head.x;snake[size - 1].y = head.y;
		score += scoreadder;
		size++;
		eat = true;
	}
	map[snake[size - 2].x][snake[size - 2].y] = char(219);
	previousmove = move;
}
void displaymenu(int & difficulty)
{
	string a[2], diff[2];diff[0] = "EASY", diff[1] = "HARD";
	a[0] = "->";
	int i = 0;
	bool select = false;
	difficulty = 0;
	while (!select)
	{
		cout << "       **********************SELECT DIFFICULTY*************************";
		for (int i = 0;i < 10;i++)
			cout << endl;
		for (int i = 0;i < 2;i++)
			cout << setw(35) << a[i] << setw(3) << diff[i] << endl << endl;
		clearscreen();
		if ((GetAsyncKeyState(VK_DOWN) != 0) && (i != 1))
		{
			a[i] = "";
			a[++i] = "->";
			difficulty = 1;

		}
		else if ((GetAsyncKeyState(VK_UP) != 0) && (i != 0))
		{
			a[i] = "";
			a[--i] = "->";
			difficulty = 0;
		}
		else if (GetAsyncKeyState(VK_RETURN) != 0)
		{
			select = true;
			system("cls");
		}

	}
}
void displayendgame(bool & playagain, int score, int highscore)
{

	string a[2], play[2];play[0] = "YES", play[1] = "NO ";
	a[0] = "->";
	int x = 0;
	bool select = false;
	while (!select)
	{
		cout << "       **********************NOOB GAME OVER*************************" << endl << endl << setw(36) << "SCORE= " << score << endl << endl << setw(40) << "HIGHSCORE= " << highscore << endl << endl << endl << setw(39) << "PLAYAGAIN?";

		for (int i = 0;i < 6;i++)
			cout << endl;
		for (int i = 0;i < 2;i++)
			cout << setw(32) << a[i] << setw(3) << play[i] << endl << endl;
		clearscreen();
		if ((GetAsyncKeyState(VK_DOWN) != 0) && (x != 1))
		{
			a[x] = "";
			a[++x] = "->";

		}
		else if ((GetAsyncKeyState(VK_UP) != 0) && (x != 0))
		{
			a[x] = "";
			a[--x] = "->";
		}
		else if (GetAsyncKeyState(VK_RETURN) != 0)
		{
			select = true;
			if (x == 0)
				playagain = true;
			else playagain = false;
			system("cls");
		}

	}

}
void initializemap(char map[n][m])
{
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < m;j++)
			if ((i == 0) || (j == 0) || (i == n - 1) || (j == m - 1))
			map[i][j] = char(240);
			else map[i][j] = ' ';
	}
}
void initializesnake(piece  *snake, int &size, int&score, char map[n][m], bool & eat, bool & playagain, string & move, string &previousmove)
{
	size = 3;
	snake[0].y = m / 2 - 1;        snake[0].x = n / 2;
	snake[1].y = m / 2;            snake[1].x = n / 2;
	snake[2].y = m / 2 + 1;        snake[2].x = n / 2;
	for (int i = 0;i < size;i++)
		map[snake[i].x][snake[i].y] = char(219);
	score = 0;
	eat = true;
	playagain = false;
	move = "right";previousmove = move;
}

int main()
{
	srand(time(0));
	char map[n][m], food = '@';
	piece foodloc, *snake = new piece[1000];
	int size, score, difficulty, count = 1, scoreadder = 10, countmove = 0, mytime = 0, myhighscore = 0;
	initializemap(map);
	bool gameover = false, eat, playagain, increment = false;
	ifstream myx;
	string move, previousmove;
	initializesnake(snake, size, score, map, eat, playagain, move, previousmove);
	displaymenu(difficulty);
	clearscreen();
	displaymap(map);
	while (!gameover)
	{
		if (increment)
			countmove++;
		if (difficulty == 0)
			Sleep(80);
		else if (difficulty == 1)
			Sleep(5);
		if ((eat) || (countmove == 40))
		{
			if ((eat) && (countmove))
				system("cls");
			for (int i = 0;i < n;i++)
			{
				for (int j = 0;j < m;j++)
					if (map[i][j] == '$')
					map[i][j] = ' ';
			}
			do
			{
				foodloc.x = rand() % n;
				foodloc.y = rand() % m;
			} while (map[foodloc.x][foodloc.y] != ' ');
			if ((count % 6 == 0) && (count))
			{
				map[foodloc.x][foodloc.y] = '$';scoreadder = 50;mytime = 39;
				increment = true;
			}
			else {
				map[foodloc.x][foodloc.y] = food;scoreadder = 10;increment = false;mytime = 0;
			}
			eat = false;
			count++;
			countmove = 0;
		}

		if (GetAsyncKeyState(VK_UP) != 0)
			move = "up";
		else if (GetAsyncKeyState(VK_DOWN) != 0)
			move = "down";
		else if (GetAsyncKeyState(VK_RIGHT) != 0)
			move = "right";
		else if (GetAsyncKeyState(VK_LEFT) != 0)
			move = "left";
		if ((move == "left") && (previousmove == "right"))
			move = "right";
		else if ((move == "right") && (previousmove == "left"))
			move = "left";
		else if ((move == "up") && (previousmove == "down"))
			move = "down";
		else if ((move == "down") && (previousmove == "up"))
			move = "up";
		movesnake(map, snake, move, size, foodloc, eat, score, previousmove, gameover, scoreadder);
		if (gameover)
		{
			ofstream myout;
			myout.open("score.txt", fstream::app);
			myout << score;
			myout << " ";
			myout.close();
			myx.open("score.txt");
			int max = 0;
			while (!myx.eof())
			{
				myx >> (myhighscore);
				myx.ignore(256, ' ');
				if (myhighscore > max)
					max = myhighscore;

			}
			myx.close();
			system("cls");displayendgame(playagain, score, max);
		}
		if (playagain)
		{
			count = 1;
			system("cls");
			displaymenu(difficulty);
			gameover = false;
			initializemap(map);
			delete[]snake;
			snake = new piece[1000];
			initializesnake(snake, size, score, map, eat, playagain, move, previousmove);
		}

		clearscreen();
		if (!gameover)
		{
			displaymap(map);
			cout << "score= " << score;
			if ((increment) && (mytime))
				cout << "    Time= " << mytime;
			else if ((!mytime) && (increment))
				system("cls");

		}
		if (map[foodloc.x][foodloc.y] == '$')
			map[foodloc.x][foodloc.y] = ' ';
		else if (map[foodloc.x][foodloc.y] == ' ')
			map[foodloc.x][foodloc.y] = '$';
		mytime--;
	}
	clearscreen();
	return 0;
}