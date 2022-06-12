#include "EditWindow.hpp"

#include "CommandWindow.hpp"
#include "MainWindow.hpp"
#include "Mushipad.hpp"

int WIDTH;
int HEIGHT;
//int xpos;
//int ypos;
int mode;
int lineNumLine;

int Loop = TRUE;

//string bufferName;

void EditWindow::editRun() {
    canINPUT = FALSE;
    printf("\033[2J"); //画面クリア
    EditWindow::xpos = LineBase+1;
    EditWindow::ypos = 0;
    printf("\033[0;0H");
	bufStart = 0;

//    SET_TITLE(bufferName);
    drawEditWindow();
	Loop = TRUE;
    while (Loop) {
        moveCursor();
		if (canINPUT)  {
			input ();
		}
    }
	Loop = FALSE;
}

void EditWindow::moveCursor() {
    int cha = 0;
    cha = getch();
    printf("\033[%d;%dH", ypos, xpos);
    switch (cha) {
        case 'j': {
            if (ypos > editH) {
                bufStart++;
				drawEditWindow();
				xpos = buffer[ypos - 2].length();
            } else if (ypos <= buffer.size()) {
                ypos++;
            }
        } break;
        case 'k': {
            if (ypos > 1) {
                ypos--;
				xpos = buffer[ypos - 2].length();
            } else if (bufStart > 0 && ypos < editH) {
                bufStart--;
                drawEditWindow();
            }
        } break;
        case 'h': {
            if (xpos > LineBase+1)
                xpos--;
        } break;
        case 'l': {
            if (xpos - LineBase < buffer[ypos - 2].length()+1)
				xpos++;
        } break;
        case 'o': {
            ypos++;
			buffer = addEnter(buffer, ypos-2);
			xpos = LineBase+1;
            canINPUT = TRUE;
        } break;
        case 'd': {
            int key2 = getch();
            switch (key2) {
                case 'd': {
                    buffer = reduceEnter(buffer, ypos - 2);
                    xpos = buffer[ypos - 2].length();
					printf("\033[2J");
                    drawEditWindow();
                } break;
            }
        } break;
        case 'i': {
            canINPUT = TRUE;
        } break;
        case ':': {
            mode = 2;
			Loop = FALSE;
        } break;
        case 27: {
            mode = 0;
        } break;
        default:
            break;
	}
    printf("\033[%d;%dH", ypos, xpos);
}

void EditWindow::drawEditWindow() {
    printf("\033[%d;%dH", 0, 0);
    SET_TITLE(bufferName);
    for (int i = bufStart; i < editH + bufStart; i++) {
        if (i < size(buffer)) {
            printf("\033[2K");
			lineNumDraw(i + 1, LineBase - 3);
			cout << buffer[i];
            cout << endl;
        } else
            // 空の場合の場所埋め
            emptyLineDraw();
    }
}

void EditWindow::transWindow() {
    printf("\033[%d;%dH", 2, 0);
    for (int i = bufStart; i < editH + bufStart; i++) {
        if (i < size(buffer)) {
            printf("\033[2K");
            lineNumDraw(i + 1, LineBase - 3);
            cout << buffer[i];
            cout << endl;
        } else
            // 空の場合の場所埋め
            emptyLineDraw();
    }
}

void EditWindow::lineNumDraw(int line, int W) {
    cout << " " << flush;
    cout << line << flush;
    for (int i = 0; i < W - Main::digit(line); i++) {
        cout << " " << flush;
    }
    cout << "| " << flush;
}

void EditWindow::input() {

    while (canINPUT) {
        int key = getch();
		string editLine = buffer[ypos - 2];

        switch (key) {
            case 10: {
				if (xpos-LineBase-1 > buffer[ypos].length()) {
					// 行の最後で改行
					ypos++;
					buffer = addEnter(buffer, ypos - 2);
					xpos = LineBase;
				}
				else {
					// 行の途中で改行
					vector<string>splitedArray = stringSplitWhenEnter(editLine, xpos-(LineBase+1));
					buffer[ypos-2] = splitedArray[0];
                    printf("\033[%d;%dH\033[0K", ypos, LineBase+1);
					cout << buffer[ypos-2] << flush;
					ypos++;
					buffer = addEnter(buffer, ypos - 2);
					buffer[ypos-2] = splitedArray[1];
                    printf("\033[%d;%dH\033[0K", ypos, LineBase+1);
					cout << buffer[ypos-2] << flush;
					editLine =  buffer[ypos-2];

				}
            } break;
            case 27: {
                canINPUT = FALSE;
            } break;
            case '\t': {
                buffer[ypos].resize(buffer[ypos].length() + 4);
                for (int i = 4; i > 0; i--) {
                    string addStr(1, ' ');
                    buffer[ypos].insert(xpos, addStr);
                    xpos++;
                }
            } break;
            case 127: {
                if (xpos - LineBase > 1) {
					// 文字編集
					vector<string> splitedArray = stringSplitWhenEnter(editLine, xpos-(LineBase+1));
					string s1 = splitedArray[0];
					s1.pop_back();
					editLine = s1 + splitedArray[1];
                    xpos--;

					// ターミナルに文字表示
                    printf("\033[%d;%dH\033[0K", ypos, LineBase+1);
					cout << editLine << flush;
                }
            } break;
            default: {
				if (xpos == 0)
					xpos = 1;
                xpos--;
                string addStr(1, (char)key);
                editLine.reserve(editLine.length());
                editLine.resize(editLine.length());
                editLine.insert(xpos - LineBase, addStr);
                cout << (char)key << flush;
                xpos+=2;
            } break;
        }
		buffer[ypos - 2] = editLine;
    }
}

void EditWindow::emptyLineDraw() {
    cout << "-" << endl;
}

void EditWindow::fileDataDraw() {}

void EditWindow::enter() {}
void EditWindow::esc() {}

vector<string> EditWindow::stringSplitWhenEnter(string s1, int index) {
	vector<string> spplited = {s1.substr(0, index), s1.substr(index)};

	return spplited;
}

vector<string> EditWindow::reduceEnter(vector<string> arr, int index) {
    //arr[ypos - 3] += arr[ypos-2];

    ypos--;
    std::string tmp = "";
    std::string tmp2 = "";

    for (int i = (ypos-2) + 1; i < size(arr) - 1; i++) { // ファイルの終了まで
        arr[i] = arr[i + 1];
    }

    // ファイル容量を一つ減らす
    arr.resize(size(arr) - 1);
    arr.reserve(size(arr) - 1);
    xpos = arr[ypos-2].length() + LineBase+1;
    return arr;
}

vector<string> EditWindow::addEnter(vector<string> arr, int index) {
    string tmp1, tmp2 = "";
    arr.resize(size(arr) + 1);
    for (int i = index; i < size(arr); i++) {
        printf("\033[1B");
        printf("\033[%d;0H", i+2);
        printf("\033[0K");
        tmp1 = arr[i];
        arr[i] = tmp2;
        tmp2 = tmp1;
		lineNumDraw(i+1, LineBase-3);
		cout << arr[i] << flush;
    }
    return arr;
}
