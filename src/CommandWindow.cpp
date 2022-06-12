#include "CommandWindow.hpp"
#include "Mushipad.hpp"
#include "EditWindow.hpp"

/*
int EditWindow::xpos;
int EditWindow::ypos;
*/

void CommandWindow::commandRun() {
    input();
    outPut("inputed  : " + InputBox::inData);
    if (InputBox::inData == "q") {
        system("clear"); // 画面消去
        printf("\033[?25h");
        for (auto tmp : buffer) {
            cout << tmp << endl;
        }
        exit(0); // 終了
    }
	if (InputBox::inData == "w") {
		std::ofstream writeFile(bufferName);
		for (auto tmp : buffer) {
			writeFile << tmp << endl;
		}
		outPut("Saved to :"+bufferName);
		//mode = 0;
	}
	/*
	if (InputBox::inData[InputBox::inData.length()-1] == 'G') {
		EditWindow::ypos = stoi(InputBox::inData.erase(InputBox::inData[InputBox::inData.length()-1]));
		EditWindow::xpos = 0;
		
	}
	*/
    inData = "";
}

void CommandWindow::input() {
    cin >> inData;
    enter();
}

void CommandWindow::esc() {
    printf("\033[2K"); // 入力行を削除
}

void CommandWindow::enter() {
    RUN = 0;
}

void CommandWindow::outPut(string outPutStr) {
    printf("\033[%d;0H", HEIGHT);                // h行目0目へカーソル移動
    printf("\033[2K");                           // 入力行を削除
    printf("\033[%luD", outPutStr.length() + 1); //カーソルを左に移動
    cout << outPutStr << flush;                  // 結果出力
}
