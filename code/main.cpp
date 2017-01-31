#include <stdio.h>
#include <string>
#include <iostream>
#include "window.h"

int main(int argv, char const* args[]) {

	Window* window = new Window("Maze Game", 1024, 920);

	window->startgame();

	delete window;
	return 0;
}