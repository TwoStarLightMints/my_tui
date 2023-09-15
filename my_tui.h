#ifndef MY_TUI
#define MY_TUI

#include <vector>
#include <string>
#include <iostream>

#if defined(_WIN32) || defined(WIN64) // Include only if on a Windows device
#include <conio.h>
#include <windows.h>
#endif

// This class is used as a wrapper to hold both the option name which will be used when
// printing the menu, and it will hold the function that will be called when the user
// selects the option
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

// Used to hold all the options for a user, collect user input and process it,
// and call the appropriate callback functions given a user's input
class Menu {
    public:
        Menu(std::string menu_name, bool numbered = false)
        : numbered(numbered)
        , menu_name(menu_name)
        {}
        void render_menu();

        void print_menu();

        void add_option(std::string name, void (*callback)());

        int get_user_action();

        int get_focus();
        void set_focus(int direction);
    
    private:
        bool numbered; // When true, menu will appear with numbers next to the options
        std::string menu_name; // Displayed at the top to the user
        std::vector<Option> options;
        int focus = 0; // This is the index of the currently selected option (i.e. if focus is 1, the second element of the options vector would be considered "selected" and if user were to hit return, the second element's callback function would be triggered)
};

#endif