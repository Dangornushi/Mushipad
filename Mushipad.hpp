#pragma once

// include
#include <cstdlib>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/ioctl.h>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>

#define ESC 0x1B
#define WAIT (10000000 / 2) /* 待ち時間 */
#define LOOP 200            /* 繰り返し回数 */
#define TRUE 1
#define FALSE 0
#define COOMAND_HEIGHT 2;

#define  SET_TITLE(__t) (cout << __t << endl)

// よく使うやつらの紹介だ!
using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::vector;

extern int unixKeyInput(void); // エコーなし環境依存特殊入力
extern int getch(void); // 文字列を表示せずに受け取ってくれる便利なやつ
extern int kbhit(void);  // 文字列入力を監視してくれる偉いやつ
extern int digit(int n); // 桁数を教えてくれる便利なやつ
extern void colorSetBack(int n); // 背景を設定してくれる奴
extern void colorSet(int n);     // 文字列の色を設定してくれる奴
extern string input(void);
extern int WIDTH;
extern int HEIGHT;
extern int mode;
extern int lineNumLine;
extern vector<string> buffer;
extern string bufferName;
