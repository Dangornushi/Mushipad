/*
 * mode :
 * 0 : Nomal
 * 1 : Insert
 * 2 : Command
 */
#pragma once

#include "CommandWindow.hpp"
#include "EditWindow.hpp"
#include "Main.hpp"
#include "Mushipad.hpp"

class MainWindow {
    void moveCursor(int key);        // カーソルを動かすなど諸々のキー設定
    void modeConfig();               // カーソル設定
    void colorSet(int color);        // 文字色設定
    void colorSetBack(int color);    // 背景色設定
    void input();                    // 標準入力
    void status();                   // 現在のモードを出力
    template <class Head, class... Tail> static void print(Head &&head, Tail &&...tail);    // 画面出力
    EditWindow                                       editWindow;       // 編集画面を司るクラス
    CommandWindow                                    commandWindow;    // コマンド入力と実行を司るクラス
    int                                              winW;             // 画面全体の横幅
    int                                              winH;             // 画面全体の縦幅

  public:
    int           xpos;        // カーソルのある行で左から何文字目か
    int           ypos;        // カーソルが今ある行数
    int           w;           // 幅
    int           h;           // 高さ
    int           lineNumW;    // 行数表示欄の幅
    int           commandLineH;
    void          Init();    // MainWindowの初期化
    void          Main();
    ~MainWindow(){};
};
