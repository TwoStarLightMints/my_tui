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
        !(focus+1 >= options.size() && direction == 2) // If adding 1 to focus does not bring focus out of index range
        &&
        !(focus-1 < 0 && direction == 1) // If subctracting 1 from focus does not bring focus out of index range
        ) {
        if (direction == 1)
            focus--;
        else if (direction == 2)
            focus++;
    }
}

int Menu::get_focus() { // TODO: Make Linux compatible version
    #if defined(_WIN32) || defined(WIN64)
        while (1) {
            if (kbhit()) {
                if (getch() == 224) { // The code 224 is sent as the initial message when an arrow key has been pressed
                    switch (getch()) { // This is the second signal sent when arrow key is pressed, this gives which arrow has been pressed
                        case 72: // Code for up arrow
                            return 1; // As stated in set_focus, move focus up when up arrow pressed
                        case 80: // Code for down arrow
                            return 2; // Similar to above, move focus down when down arrow pressed
                    }
                }
            }
        }
    #endif // _WIN32 || WIN64
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