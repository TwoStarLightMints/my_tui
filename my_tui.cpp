#include "my_tui.h"


/*================================================================================================================*/
//
// Implement the class
//
/*================================================================================================================*/

void Menu::print_menu() {
    for (int i = 0; i < options.size(); i++) {
        if (i == focus) {
            std::cout << i+1 << ". " << "\033[3;47;30m " << options[i] << " \033[0m" << '\n'; // This uses ANSI escape color codes to indicate
                                                                                              //  focus of menu items
        } else {
            std::cout << i+1 << ". " << options[i] << '\n';
        }
    }
}

void Menu::add_option(std::string new_opt) {
    options.push_back(new_opt);
}

void Menu::set_focus(int direction) {
    if (!(focus+1 >= options.size() && direction == 1) && !(focus-1 < 0 && direction == 2)) {
        if (direction == 1)
            focus++;
        else if (direction == 2)
            focus--;
    }
}