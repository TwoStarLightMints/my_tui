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