/****************************************************************************
  FileName     [ myGetChar.cpp ]
  PackageName  [ util ]
  Synopsis     [ Non-buffered get-char function ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyright(c) 2023-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#include <ctype.h>
#include <stdlib.h>
#include <termios.h>

#include <iostream>

using namespace std;

//----------------------------------------------------------------------
//    Global static funcitons
//----------------------------------------------------------------------
static struct termios stored_settings;

static void reset_keypress(void) {
    tcsetattr(0, TCSANOW, &stored_settings);
}

static void set_keypress(void) {
    struct termios new_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_lflag &= (~ECHO);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0, &stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
}

//----------------------------------------------------------------------
//    Global functions
//----------------------------------------------------------------------
char myGetChar(istream& istr) {
    char ch;
    set_keypress();
    istr.unsetf(ios_base::skipws);
    istr >> ch;
    istr.setf(ios_base::skipws);
    reset_keypress();
    return ch;
}

char myGetChar() {
    return myGetChar(cin);
}
