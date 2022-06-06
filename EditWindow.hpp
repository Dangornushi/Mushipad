#pragma once

#include "CommandWindow.hpp"
#include "InputBox.hpp"

#include <sstream>

class EditWindow : public InputBox {
    vector<string> filedata; // 開いたファイルの内容
    int fileLine;            // fileの大きさ
    int canINPUT;
    int bufStart; // bufferの表示が開始される位置、デフォルトは0、カーソルが下限に到達するたびにインクリメント、上限に到達するたびにデクリメント
    int nowBestLine;                   // 画面に描写している行数
    void title();                      // titleを描画する
    void input();                      // 入力
    void moveCursor();                 // カーソルを動かす
    void transWindow();                // ウィンドウのページをスクロール
    void fileDataDraw();               // フィル内容を描写
    void emptyLineDraw();              // 空行を描写
    void drawEditWindow();             //  EditWindowを描画する
    void lineNumDraw(int line, int W); // 行数の表示
    vector<string> stringSplitWhenEnter(string s1, int index);
    vector<string> addEnter(vector<string> arr, int index);
    vector<string> reduceEnter(vector<string> arr, int index);

  public:
    static int editW;    // 編集ウインドウの幅
    static int editH;    // 編集ウインドウの高さ
    static int xpos;     // カーソルのX座標
    static int ypos;     // カーソルのY座標
    static int LineBase; // 行数表示欄の幅

    void editRun();
    void enter();
    void esc();
    virtual ~EditWindow(){};
};
