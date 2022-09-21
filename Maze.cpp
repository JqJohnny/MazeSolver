#include "Maze.h"

Maze::Maze()
{
	// Making a test maze by hand to make testing easy without giving away the extra credit of the maze maker.
	mStart = new Cell;
	mStart->mNorth = new Cell;
	mStart->mNorth->mNorth = new Cell;
	mStart->mNorth->mNorth->mEast = new Cell;
	mStart->mNorth->mNorth->mIsExit = true;
	//mStart->mEast = new Cell;
	//mStart->mEast->mEast = new Cell;
	//mStart->mEast->mEast->mNorth = new Cell;
	//mStart->mEast->mEast->mNorth->mNorth = new Cell;
	//mStart->mWest = new Cell;
	//mStart->mWest->mWest = new Cell;
	//mStart->mWest->mWest->mNorth = new Cell;
	//mStart->mWest->mWest->mNorth->mIsExit = true;
	//mStart->mEast->mEast->mNorth->mNorth->mIsExit = true;
	// This is a big U 
	

	//Text File 
	if (mStart == nullptr)
		mStart = new Cell;
	arrayLength = MazeDimension(1);
	arrayHeight = MazeDimension(0);
	arraySize = arrayLength * arrayHeight;  // Length * Height
	char* arrayMaze = new char[arraySize]; // SampleText is 38 x 10 = 380
	char* destructor = new char[arraySize];
	std::ifstream mazeFile;
	mazeFile.open("SampleMaze.txt", std::ios::in); // Insert any Maze here!!!  <--- Also change file open in MazeDimension
	if (mazeFile.is_open())
	{
		while (std::getline(mazeFile, line))
		{
			lineNumber++;
			for (int i = 0; i < line.length(); i++) //Handles the case that arrays start at 0
			{
				arrayMaze[i + arrayLength * (lineNumber - 1)] = line.at(i);

			}
		}
	}
	for (int i = 0; i <= (arraySize - 1); i++) // Prints out the maze from an array
	{
		std::cout << arrayMaze[i];
		if (i % (arrayLength - 1) == 0 && i != 0 && i <= (arrayLength - 1))
		{
			std::cout << std::endl;
		}
		if ((i + 1) % arrayLength == 0 && i > arrayLength)
		{
			std::cout << std::endl;
		}
	}
	for (int i = 0; i <= (arraySize - 1); i++)
	{
		if (arrayMaze[i] == 'S')
		{
			StartIndex = i;
		}
		if (arrayMaze[i] == 'E')
		{
			EndIndex = i;
		}
	}

	MazeGenerator(arrayMaze, StartIndex, mStart); // Comment this out for hard-coded mazes
	mazeFile.close();
	delete[] arrayMaze;
}

bool Maze::MazeGenerator(char arrayN[], int tCurrent, Cell* NewCell) // Uses recursion to generate the maze
{
	if (arrayN[tCurrent - arrayLength] == 'E')
	{
		NewCell->mNorth = new Cell;
		NewCell->mNorth->mIsExit = true;
		VectorOfPointers.push_back(NewCell->mNorth);
		return true;
	}
	if (arrayN[tCurrent + 1] == 'E')
	{
		NewCell->mEast = new Cell;
		NewCell->mEast->mIsExit = true;
		VectorOfPointers.push_back(NewCell->mEast);
		return true;
	}
	if (arrayN[tCurrent + arrayLength] == 'E')
	{
		NewCell->mSouth = new Cell;
		NewCell->mSouth->mIsExit = true;
		VectorOfPointers.push_back(NewCell->mSouth);
		return true;
	}
	if (arrayN[tCurrent - 1] == 'E')
	{
		NewCell->mWest = new Cell;
		NewCell->mWest->mIsExit = true;
		VectorOfPointers.push_back(NewCell->mWest);
		return true;
	}

	if (arrayN[tCurrent - arrayLength] == ' ') // Above
	{
		arrayN[tCurrent - arrayLength] = 'P';
		NewCell->mNorth = new Cell;
		VectorOfPointers.push_back(NewCell->mNorth);
		MazeGenerator(arrayN, tCurrent - arrayLength, NewCell->mNorth);
	}
	if (arrayN[tCurrent + 1] == ' ') // Right
	{
		arrayN[tCurrent + 1] = 'P';
		NewCell->mEast = new Cell;
		VectorOfPointers.push_back(NewCell->mEast);
		MazeGenerator(arrayN, tCurrent + 1, NewCell->mEast);
	}
	if (arrayN[tCurrent + arrayLength] == ' ') // Below
	{
		arrayN[tCurrent + arrayLength] = 'P';
		NewCell->mSouth = new Cell;
		VectorOfPointers.push_back(NewCell->mSouth);
		MazeGenerator(arrayN, tCurrent + arrayLength, NewCell->mSouth);
	}
	if (arrayN[tCurrent - 1] == ' ') // Left
	{
		arrayN[tCurrent - 1] = 'P';
		NewCell->mWest = new Cell;
		VectorOfPointers.push_back(NewCell->mWest);
		MazeGenerator(arrayN, tCurrent - 1, NewCell->mWest);
	}
	return false;
}

Maze::~Maze() // Destrucor here
{
	while (!VectorOfPointers.empty())
	{
		delete VectorOfPointers.back();
		VectorOfPointers.back() = nullptr;
		VectorOfPointers.pop_back();
	}
	delete mStart;
	delete[] arrayMaze;
	arrayMaze = nullptr;
}

bool Maze::MazeRecursive( Maze::Cell* tCurrent, std::stack<std::string>* tPath )
{
	if (tCurrent->mIsExit) // Base case
	{
		std::cout << "Exit Found.\n";
		return true;
	}

	if (tCurrent->mNorth == nullptr || tCurrent->mNorth->mProcessed == true)
		if (tCurrent->mEast == nullptr || tCurrent->mEast->mProcessed == true)
			if (tCurrent->mSouth == nullptr || tCurrent->mSouth->mProcessed == true)
				if (tCurrent->mWest == nullptr || tCurrent->mWest->mProcessed == true)
				{
					tPath->pop();
					return false;
				}

	tCurrent->mProcessed = true;
	if (tCurrent->mNorth != nullptr && tCurrent->mNorth->mProcessed != true) // Fork Check
	{
		std::string north = "North";
		tPath->push(north);
		if (MazeRecursive(tCurrent->mNorth, tPath))
			return true;
	}
	if (tCurrent->mEast != nullptr && tCurrent->mEast->mProcessed != true)
	{
		std::string east = "East";
		tPath->push(east);
		if (MazeRecursive(tCurrent->mEast, tPath))
			return true;
	}
	if (tCurrent->mSouth != nullptr && tCurrent->mSouth->mProcessed != true)
	{
		std::string south = "South";
		tPath->push(south);
		if (MazeRecursive(tCurrent->mSouth, tPath))
		{
			return true;
		}
	}
	if (tCurrent->mWest != nullptr && tCurrent->mWest->mProcessed != true)
	{
		std::string west = "West";
		tPath->push(west);
		if (MazeRecursive(tCurrent->mWest, tPath))
			return true;
	}
	tPath->pop();
	return false;
}
int Maze::MazeDimension(int x) // 0 for Position // 1 for Line number
{
	int lineNumber = 0;
	std::ifstream mazeFile;
	mazeFile.open("SampleMaze.txt", std::ios::in); // Change maze file here too!
	if (mazeFile.is_open()) { //checking whether the file is open
		while (std::getline(mazeFile, line))
		{
			lineNumber++;
		}
		if (x == 0)
			return lineNumber;
		else if (x == 1)
			return line.length();
	}
	return 0;
}


std::stack<std::string> Maze::SolveMaze()// Driver
{
	// Don't need to change this.
	std::stack<std::string> tAnswer;
	MazeRecursive( mStart, &tAnswer );
	return tAnswer;
}