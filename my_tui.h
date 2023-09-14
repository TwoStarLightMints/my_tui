#ifndef MY_TUI
#define MY_TUI
#include <vector>
#include <string>
#include <iostream>
#include <termios.h>

class Option {
    public:
        Option(std::string name, void (*callback)())
            : name(name)
            , callback(callback)
            {}
        
        std::string to_string();

        void action();
    private:
        std::string name;
        void (*callback)();
};

class Menu {
    public:
        Menu() {}
        void print_menu();
        void add_option(std::string name, void (*callback)());
        void set_focus(int direction);
        int get_focus();
    
    private:
        std::vector<Option> options;
        int focus = 0;
};

#endif