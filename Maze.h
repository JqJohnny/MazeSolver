#pragma once
#include <stack>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Maze
{
public:
	class Cell
	{
		friend Maze;
		Cell* mNorth = nullptr; // While this "hardcodes" four directions, it is hella easier and 99% of mazes are flat and square
		Cell* mSouth = nullptr;
		Cell* mEast = nullptr;
		Cell* mWest = nullptr;
		int tempLength = 0;
		bool mIsExit = false;
		bool mProcessed = false; // Prevent loops  Treat finding a processed cell as just not there.  Like a dead end.
	};

private:
	bool MazeRecursive( Cell* tCurrent, std::stack<std::string>* tPath );
	Cell* mStart;
	std::string line;
	int i = 0;
	int Length = 0;
	int lineNumber = 0;
	int StartIndex = 0;
	int EndIndex = 0;
	int arrayLength = 0;
	int arrayHeight = 0;
	int arraySize = 0;
	int x = 0;
	char* arrayMaze;
	int MazeDimension(int x);
	bool MazeGenerator(char arrayN[], int tCurrent, Cell* NewCell);
	std::vector<Cell*> VectorOfPointers;
public:
	Maze();// Making a constructor with a file name would be cool for the extra credit.
	~Maze();
	std::stack<std::string> SolveMaze();
};

