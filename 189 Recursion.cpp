// 189 Recursion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Maze.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	Maze tTestMaze;
	std::stack<std::string> tPath;
	tPath = tTestMaze.SolveMaze();
	std::cout << "Read from the bottom up\n";
	for (std::stack<std::string> dump = tPath; !dump.empty(); dump.pop())
		std::cout << dump.top() << '\n';
	_CrtDumpMemoryLeaks();
}

