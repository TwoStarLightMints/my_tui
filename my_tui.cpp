#include "my_tui.h"
#include <termios.h>

void custom_pause() {
    std::cout << "Press enter to continue...";
    std::cin.get();
}

/*================================================================================================================*/
//
// Implement menu
//
/*================================================================================================================*/

void Menu::render_menu() { // TODO: Hide cursor on Linux machines
    int cont;
    
    #ifdef _WIN32 // Hide cursor on Windows, found in https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt by Captain Oblivious
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(out, &cursor_info);
    cursor_info.bVisible = false;
    SetConsoleCursorInfo(out, &cursor_info);
    #endif

    do {
        system("clear");

        print_menu();

        cont = get_user_action();
    } while (cont); // While user is still performing actions within this render loop and has not pressed q, continue

    #ifdef _WIN32 // Unhide cursor on Windows
    out = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(out, &cursor_info);
    cursor_info.bVisible = true;
    SetConsoleCursorInfo(out, &cursor_info);
    #endif
}

void Menu::print_menu() {
    std::cout << "\033[1;4m" << menu_name << "\033[0m" << "\n\n";
    for (int i = 0; i < options.size(); i++) {
        if (i == focus) { // If the focus index matches the current item, use ANSI escape color codes to indicate focus to user
            if (numbered) {
                std::cout << i+1 << ". " << "\033[30;47m " << options[i].to_string() << " \033[0m" << '\n';
            } else {
                std::cout << "\033[30;47m " << options[i].to_string() << " \033[0m" << '\n';
            }
        } else {
            if (numbered) {
                std::cout << i+1 << ". " << options[i].to_string() << '\n';
            } else {
                std::cout << options[i].to_string() << '\n';
            }
        }
    }

    std::cout << "\nUse arrow keys and enter to interact with menu, or q to quit\n";
}

void Menu::add_option(std::string name, void (*callback)()) {
    options.push_back(Option(name, callback));
}

int Menu::get_user_action() { // Abstracts away the get_focus and set_focus helper functions and allows natural user interaction
    int decision = Menu::get_focus(); // Get the user's input

    if (decision == 1 || decision == 2) { // Branch if the user is moving focus
        Menu::set_focus(decision);
    } else if (decision == 0) { // Branch if user wants to execute the option which is focused
        options[focus].action(); // Select focused option using the focus attribute, then call that option's action method to execute it's callback function
    } else if (decision == -1) {
        return 0; // End render loop
    }

    return 1; // Continue render loop
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

#ifdef __linux__
char getch_l() { // This solution was found at https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed, by anon and Falcon Momot
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsettattr ~ICANON");
    return buf;
}
#endif

int Menu::get_focus() { // TODO: Make Linux compatible version
        while (1) {
            #ifdef _WIN32
                if (kbhit()) {
                    int code = getch();
                    if (code == 224) { // The code 224 is sent as the initial message when an arrow key has been pressed
                        switch (getch()) { // This is the second signal sent when arrow key is pressed, this gives which arrow has been pressed
                            case 72: // Code for up arrow
                                return 1; // As stated in set_focus, move focus up when up arrow pressed
                            case 80: // Code for down arrow
                                return 2; // Similar to above, move focus down when down arrow pressed
                        }
                    } else if (code == 13) { // This is the code for pressing the return key
                        return 0;
                    } else if (code == 113) { // This is the code for the q key, returning -1 will exit the current menu render loop
                        return -1;
                    }
                }
            #elif __linux__
                int code = getch_l();
                if (code == 27 && getch_l() == 91) { 
                    switch (getch_l()) {
                        case 65: // Code for up arrow key on linux (at the time of writing only tested on Arch Linux)
                            return 1;
                        case 66: // Code for the down arrow key on linux (at the time of writing only tested on Arch Linux)
                            return 2;
                    }
                } else if (code == 10) { // This is the code for pressing the return key
                    return 0;
                } else if (code == 113) { // This is the code for pressing q
                    return -1;
                }
            #endif
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