// PDCursesSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#define BUFFSIZE 128
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <chrono>

struct Tetris {
	char tetrimino1[BUFFSIZE];
	char tetrimino2[BUFFSIZE];
	char tetrimino3[BUFFSIZE];
};

int main(int argc, char* argv[])
{
	struct Tetris tetris[BUFFSIZE] = {
		{//I
			"","","■■■■"
		},
		{//L
			"","■","■■■"
		}
	};

	// 初期化
	if (initscr() == NULL) {
		return 1;
	}

	int i = 0;
	int x = 0;
	int j = 0;

	//計測スタート時間を保存
	auto start = std::chrono::system_clock::now();

	while (1) {
		int v = 0;//テトリミノの種類
		v = rand() % 2;

		while (j+5<26) {
			// 画面をクリア
			erase();

			// フィールド
			mvaddstr(1, 5, "Tetris Game");//題名
			
			for (i = 0; i < 23; i++) {
				mvaddstr(i + 3, 50, "|");//縦軸
			}
			for (i = 0; i < 50; i++) {
				mvaddstr(26, i, "-");//横軸
			}
			//タイマ表示
			for (i = 0;i<500; i++) {
				mvaddstr(5, 55, "i");//縦軸
			}
			
			//テトリス生成
			mvaddstr(j + 3, 5 + x, tetris[v].tetrimino1);
			mvaddstr(j + 4, 5 + x, tetris[v].tetrimino2);
			mvaddstr(j + 5, 5 + x, tetris[v].tetrimino3);
			j++;

			//キーボード
			int key;
			initscr();
			noecho();
			cbreak();
			keypad(stdscr, TRUE);
			move(j, x);
			key = getch();
			if (key == 'q')break;
			switch (key) {
			//case KEY_UP:y--; break;
			case KEY_DOWN:j++; break;
			case KEY_LEFT:x--; break;
			case KEY_RIGHT:x++; break;
			}
		}
		//画面にテトリスを残したままにする
		if (j + 5 == 25) {
			x=j + 3;
			mvaddstr(j + 3, 5 + x, tetris[v].tetrimino1);
			mvaddstr(j + 4, 5 + x, tetris[v].tetrimino2);
			mvaddstr(j + 5, 5 + x, tetris[v].tetrimino3);
			j = 0;
		}
		//}
		//endwin();
		//return(0);
		// 画面を更新
	}
	refresh();
	// 1秒待機
	napms(1000);
	//計測終了時刻を保存
	auto end = std::chrono::system_clock::now();
	auto dur = end - start;
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	std::cout << msec << "milli sec \n";
}