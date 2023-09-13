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
        std::vector<Option> options;
        int focus = 0;
};

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

#endif