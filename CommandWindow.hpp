#pragma once

#include "Mushipad.hpp"
#include "InputBox.hpp"

class CommandWindow : public InputBox {
    string         commandStr;
    vector<string> CommandS;

  public:
    void        commandRun();
    void        input();
    void        enter();
    void        esc();
    static void outPut(string outPutStr);
};
