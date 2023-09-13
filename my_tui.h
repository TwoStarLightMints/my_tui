#ifndef MY_TUI
#define MY_TUI
#include <vector>
#include <string>
#include <iostream>

class Menu {
    public:
        Menu() {}
        void print_menu();
        void add_option(std::string new_opt);
        void set_focus(int direction);
    
    private:
        std::vector<std::string> options;
        int focus = 0;
};

#endif