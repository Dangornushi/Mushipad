#pragma once

#include "Mushipad.hpp"
#include "Main.hpp"

/*
 * 文字入力の基底クラス
 * inout:
 * 		DataをEnterが入力されるまでinDataに格納する
 * enter:
 *		inputにてEnterが入力されると呼び出される仮想関数
 *		行う動作は派生クラスにて定義される
 */
class InputBox {
    int W;
    int h;
    int x;
    int y;

  public:
	int RUN;
    string inData;
    virtual void input();
    virtual void enter();
	virtual void esc();
    void print();
};
