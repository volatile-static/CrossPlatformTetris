#include"Tetris.h"
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<Windows.h>
using namespace std;

bool board[50][50];

void Update(TCmd* Messenger) {
	for (int i(0); i < Messenger->cnt[0]; ++i)
		board[Messenger->Erase[i].Y][Messenger->Erase[i].X] = false;
	for (int i(0); i < Messenger->cnt[1]; ++i)
		board[Messenger->Paint[i].Y][Messenger->Paint[i].X] = true;
	for (int i(0); i < SizeX; ++i) {
		for (int j(0); j < SizeY; ++j)
			if (board[i][j])
				cout << '*';
			else
				cout << ' ';
		cout << endl;
	}
}

int main() {
	srand(123);
	TCmd msg;
	NewGame(&msg);
	while (1) {
		if (!MoveDown(&msg))
			continue;
		system("cls");
		Update(&msg);
		if (GameOver()) {
			for (int i(0); i < SizeX; ++i)
				for (int j(0); j < SizeY; ++j)
					board[i][j] = false;
			NewGame(&msg);
		}
		if (GetAsyncKeyState(VK_LEFT))
			MoveLeft(&msg);
		system("cls");
		Update(&msg);
		if (GetAsyncKeyState(VK_RIGHT))
			MoveRight(&msg);
		system("cls");
		Update(&msg);
		if (GetAsyncKeyState(VK_UP))
			Transform(&msg);
		system("cls");
		Update(&msg);
		Sleep(100);
	}
	return 0;
}
