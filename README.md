# my_tui
my_tui is a very simple C++ TUI library. I am currently actively developing it and clearly have a long ways to go.

## Warning
my_tui is in a very volatile state and is bound to change at any point, so bare this in mind when implementing it in your project.

## Usage
To use my_tui, first clone the git repo
```
git clone https://github.com/TwoStarLightMints/my_tui.git
```
Then, copy both my_tui.cpp and my_tui.h into your project root directory.
```
proj_root
| your_proj.cpp
| my_tui.cpp
| my_tui.h
```
And lastly, compile using your choice of build system
```
g++ -o main your_proj.cpp my_tui.cpp
```

## Example
Currently, my_tui works with two major concepts, Menus and Options. Each Menu contains a "menu_name" and a vector of any number of Option objects.
Each Option contains a "title" and a callback function.  
In your project, first create a Menu object:
```
...

int main() {
    Menu my_menu = Menu("Main Menu);
}

...
```
This first menu object will act as your main or root menu. You can pass in whatever name you would like to serve as the display name for the user of your application.
From here, you will then add Option objects to your menu using the `add_option()` instance method.
```
...

void say_hello() {
    std::cout << "Hello, World!\n";
}

int main() {
    Menu my_menu = Menu("Main Menu");

    my_menu.add_option("say hello", &say_hello);
}

...
```
As you can see, you must pass in the name of the option, in this case "say hello", and a function pointer to the callback function you would like to use, in this case `void say_hello()`. Callback functions should have the return type `void` and have no parameters. Let's add some more options.
```
...

void say_hello() {
    std::cout << "Hello, World!\n";
}

void foo() {
    int x = 10;
    int y = 5;

    std::cout << "10 + 5 =" << x - y << '\n';
}

void bar() {
    int bonk = 4;

    std::cout << "bonk is " << ((bonk % 2 == 0) ? "even" : "not even") << '\n';
}

int main() {
    Menu my_menu = Menu("Main Menu");

    my_menu.add_option("say hello", &say_hello);
    my_menu.add_option("foo", &foo);
    my_menu.add_option("bar", &bar);
}

...
```
Now that we have a sizable list, let's get to actually displaying our TUI to our users. In order to do this, you simply call `render_menu()`
```
...

void say_hello() {
    std::cout << "Hello, World!\n";
}

void foo() {
    int x = 10;
    int y = 5;

    std::cout << "10 + 5 =" << x - y << '\n';
}

void bar() {
    int bonk = 4;

    std::cout << "bonk is " << ((bonk % 2 == 0) ? "even" : "not even") << '\n';
}

int main() {
    Menu my_menu = Menu("Main Menu");

    my_menu.add_option("say hello", &say_hello);
    my_menu.add_option("foo", &foo);
    my_menu.add_option("bar", &bar);

    my_menu.render_menu();
}

...
```
`render_menu()` handles many behind the scenes concerns so you can focus on creating the interface and functionality for your app.