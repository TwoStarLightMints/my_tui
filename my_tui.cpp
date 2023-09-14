#include "my_tui.h"


/*================================================================================================================*/
//
// Implement menu
//
/*================================================================================================================*/

void Menu::print_menu() {
    for (int i = 0; i < options.size(); i++) {
        if (i == focus) {
            std::cout << i+1 << ". " << "\033[3;47;1m " << options[i].to_string() << " \033[0m" << '\n'; // This uses ANSI escape color codes to indicate
                                                                                                         //  focus of menu items
        } else {
            std::cout << i+1 << ". " << options[i].to_string() << '\n';
        }
    }
}

void Menu::add_option(std::string name, void (*callback)()) {
    options.push_back(Option(name, callback));
}

void Menu::set_focus(int direction) {
    if (!(focus+1 >= options.size() && direction == 1) && !(focus-1 < 0 && direction == 2)) {
        if (direction == 1)
            focus++;
        else if (direction == 2)
            focus--;
    }
}

int Menu::get_focus() {
    while (1) {
        if (kbhit()) {
            std::cout << static_cast<char>(getch()) << '\n';
        }
    }
}

/*================================================================================================================*/
//
// Implement option
//
/*================================================================================================================*/

std::string Option::to_string() {
    return name;
}

void Option::action() {
    callback();
}