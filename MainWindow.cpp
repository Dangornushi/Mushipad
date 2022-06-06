#include "MainWindow.hpp"

struct winsize Main::ws;

int EditWindow::xpos;
int EditWindow::ypos;
int EditWindow::editW;
int EditWindow::editH;
int EditWindow::LineBase;

string bufferName;

void MainWindow::Init() {
    printf("%c[2J\n", ESC);    // 画面消去
    printf("\033[0;0H\n");     // 0行目0目へカーソル移動
    if (~ioctl(STDOUT_FILENO, TIOCGWINSZ, &Main::ws)) {
        w = Main::ws.ws_col;
        h = Main::ws.ws_row;    // コマンド列分マイナス
    } else {
        perror("ioctl");
    }
    commandLineH = 0;
//	bufferName = "title"; // タイトルの名前を設定
}

void MainWindow::Main() {
    EditWindow::LineBase = Main::digit(size(buffer)) + 4;
    EditWindow::editW = WIDTH - EditWindow::LineBase;
    EditWindow::editH = HEIGHT - 3;

    EditWindow::xpos = 0;
    EditWindow::ypos = 0;

    while (1) {
        if (mode == 1) {
            editWindow.editRun();
        }

        if (mode == 2) {
            // mode描写の更新
            status();
            printf("\033[%d;0H", h - 1); // h行目0目へカーソル移動
            printf("\033[2K");           // 入力行を削除
            cout << "> " << flush;

            commandWindow.commandRun();
            mode = 1;
            printf("\033[2K"); // 入力行を削除
        }
        //status();
        //modeConfig();
        printf("\033[0;0H"); // h行目0目へカーソル移動
   }
}

/* ひとつ以上のパラメータを受け取るようにし、可変引数を先頭とそれ以外に分割する
 * Head = 先頭
 * Tail = それ以外
 */
template <class Head, class... Tail> void MainWindow::print(Head &&head, Tail &&...tail) {
    cout << head << endl;

    // パラメータパックtailをさらにheadとtailに分割する
    print(move(tail)...);
}

// パラメータパックが空になったら終了
void print();

void MainWindow::status() {
    printf("\033[%d;0H", h);    // h行目0目へカーソル移動
    printf("\033[2K");          //カーソル位置の行をクリア
    switch (mode) {
        case 0:
            cout << "Nomal" << flush;
            break;
        case 1:
            cout << "Edit" << flush;
            break;
        case 2:
            cout << "Command" << flush;
            break;
        default:
            cout << flush;
            break;
    }
    //printf("\033[%d;%dH", ypos, lineNumW + xpos);    // h行目0目へカーソル移動
}

void MainWindow::input() {}

void MainWindow::moveCursor(int key) {}

void MainWindow::modeConfig() {
//    printf("\e[?25l");    // カーソル削除
    switch (mode) {
        case 0:
            printf("\033[%d;%dH", ypos, xpos);    // 0行目0目へカーソル移動
            break;
        case 1:
            printf("\033[%d;0H", ypos + 2);    // 0行目0目へカーソル移動
        case 2:
            printf("\033[%d;0H", h);    // 10行目0目へカーソル移動
        default:
            printf("\e[?25h");    // カーソル復活祭(イースター)
            break;
    }
}

void MainWindow::colorSet(int color) {
    cout << "\x1b[38;5;" << color << "m" << flush;
}

void MainWindow::colorSetBack(int color) {
    cout << "\x1b[48;5;" << color << "m" << flush;
}

