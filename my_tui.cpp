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
    // Passing in 1 moves the selection up (i.e. if user selection was 2, then it would be 1)
    // Passing in 2 moves the selection down (i.e. if user selection was 1, then it would be 2)
    if (
        !(focus+1 >= options.size() && direction == 1) // If adding 1 to focus does not bring focus out of index range
        &&
        !(focus-1 < 0 && direction == 2) // If suctracting 1 from focus does not bring focus out of index range
        ) {
        if (direction == 1)
            focus++;
        else if (direction == 2)
            focus--;
    }
}

int Menu::get_focus() { // TODO: Allow user to change focus by simply pressing the up and down arrow keys, input must be unbuffered (i.e. user hits key, something happens NOT user hits key, then return, then something happens)
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

std::string Option::to_string() { // Used when presenting the option in the menu
    return name;
}

void Option::action() { // Activiates the option's callback function
    callback();
}