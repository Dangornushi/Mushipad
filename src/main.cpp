
#include "Main.hpp"
#include "Mushipad.hpp"
#include "MainWindow.hpp"

int Main::digit(int n) {
  int c = 0;

  while (1) {
      if (n < 10)
	  break;
      n /= 10;
      c++;
  }
  return c + 1;
}

int main(int argc, char **argv) {

    if (~ioctl(STDOUT_FILENO, TIOCGWINSZ, &Main::ws)) {
        WIDTH = Main::ws.ws_col;
        HEIGHT = Main::ws.ws_row;    // コマンド列分マイナス
    } else {
        perror("ioctl");
    }
	mode = 1;
	int lineNum = 0;
	int autoSave = TRUE; 
	if ( argc > 1) {
        string line;
        string openFileName; 
        lineNum = 0;
        openFileName = argv[1];
        std::ifstream input_file(openFileName, std::ios::in);
        if (!input_file) {
            std::cout << "Could not open the file : '" << openFileName <<  "'" << std::endl;
            return 0;
        }
        else {
            while (getline(input_file, line)) {
                buffer.push_back(line);
                lineNum++;
            }
            if (lineNum == 0) {
                lineNum++;
                buffer.push_back("\n");
            }
            lineNum--;
            input_file.close();
		bufferName = openFileName;
        }
    }
	else {
		buffer = { };
	}
    MainWindow mainWindow;
    mainWindow.Init();
    mainWindow.Main();
    printf("%c[39m", ESC); /* 文字色を戻す */
}
