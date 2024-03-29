#include <bits/stdc++.h>
using namespace std;

class SudokuGrid
{
	int grid[9][9];

public:
	SudokuGrid()
	{
		menu();
	}

private:
	void menu()
	{
		cout << "\n=========================================\n";
		cout << "              Sudoku Script\n";
		cout << "=========================================\n\n";
		cout << "Welcome to Sudoku Script!\n";
		cout << "Before we start, you will have to input the puzzle into this program.\n\n";
		cout << "You can either:-\n";
		cout << "\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
		cout << "\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
		cout << "\t   The file must not have a name > 20 characters.\n";
		cout << "\t   The file must be in the same directory as this C++ file.\n";
		cout << "\t   The file must have all 81 values seperated with spaces.\n";
		cout << "\t   Blank cells must be filled in as 0 (eg; 1 0 0  2 0 0 ...).\n";
		cout << "\t   --> ";
		string option;
		cin >> option;
		if (option == "1")
			readFromConsole();
		else if (option == "2")
			readFromFile();
		else
		{
			while (true)
			{
				cout << "\nYou seem to have entered an invalid option. Try again.\n";
				cout << "\t   --> ";
				cin >> option;
				if (option == "1")
					readFromConsole();
				else if (option == "2")
					readFromFile();
				else
					continue;
				break;
			}
		}
	}

private:
	void readFromConsole()
	{
		cout << "\nEnter the specified value when prompted.\n";
		cout << "Enter 0 if cell is empty.\n\n";
		int rowIter, colIter;
		for (rowIter = 0; rowIter < 9; rowIter++)
		{
			for (colIter = 0; colIter < 9; colIter++)
			{
				int enteredValue;

				cout << "Enter value for cell[" << rowIter + 1 << "][" << colIter + 1 << "] --> ";
				cin >> enteredValue;

				if (!(enteredValue >= 0 && enteredValue <= 9))
				{
					while (true)
					{
						cout << "Oops! You seem to have entered a wrong value! Try again.\n";
						cout << "Enter value for cell [" << rowIter + 1 << "][" << colIter + 1 << "] --> ";
						cin >> enteredValue;

						if (enteredValue >= 0 && enteredValue <= 9)
							break;
					}
				}

				grid[rowIter][colIter] = enteredValue;
			}
			cout << "-------\n";
		}
		cout << endl;
	}
//function to read from file
private:
	void readFromFile()
	{
		char filename[30];
		cout << "\nEnter the name of the file that contains the Sudoku Puzzle.\n";
		cout << "\t   --> ";
		cin >> filename;
		ifstream input_file;
		input_file.open(filename, ios::in);
		int rowIter, colIter;
		for (rowIter = 0; rowIter < 9; rowIter++)
		{
			for (colIter = 0; colIter < 9; colIter++)
			{
				int readValue;
				input_file >> readValue;
				if (!(readValue >= 0 && readValue <= 9))
				{
					cout << "\nValue " << ((rowIter * 9) + colIter + 1) << " in " << filename;
					cout << " seems to be wrong! Correct the value and try again!\n";
					exit(EXIT_FAILURE);
				}
				grid[rowIter][colIter] = readValue;
				if (input_file.eof())
					break;
			}
		}
		input_file.close();
		cout << endl;
	}

public:
	void setCellValue(int row, int col, int key)
	{
		grid[row][col] = key;
	}

public:
	int getCellValue(int row, int col)
	{
		int cellValue = grid[row][col];
		return cellValue;
	}

public:
	void displayGrid()
	{
		cout << "++=====================================++";
		int rowIter, colIter;
		for (rowIter = 0; rowIter < 9; rowIter++)
		{
			int cellIter = 1;

			cout << "\n||";
			for (colIter = 0; colIter < 9; colIter++)
			{
				if (cellIter == 3)
				{
					cout << " ";
					if (grid[rowIter][colIter] != 0)
						cout << grid[rowIter][colIter] << " ";
					else
						cout << "  ";
					cout << "||";
					cellIter = 1;
				}
				else
				{
					cout << " ";
					if (grid[rowIter][colIter] != 0)
						cout << grid[rowIter][colIter] << "  ";
					else
						cout << "   ";
					cellIter++;
				}
			}
			if (rowIter % 3 != 2)
				cout << "\n++-----------++-----------++-----------++";
			else
				cout << "\n++=====================================++";
		}
		cout << " ";
	}
};

class SudokuSolver
{
	int recursiveCount;
	SudokuGrid grid;

public:
	SudokuSolver()
	{
		recursiveCount = 0;

		displayGrid();
		cout << "\n\nCalculating possibilities...\n";
		cout << "Backtracking across puzzle....\n";
		cout << "Validating cells and values...\n\n";

		solve();

		displayGrid();
		cout << "\n\n";
	}

private:
	bool cellValueValid(int row, int col, int keyValue)
	{
		int rowIter, colIter;
		for (rowIter = 0; rowIter < 9; rowIter++)
		{
			if (rowIter == row)
				continue;
			if (grid.getCellValue(rowIter, col) == keyValue)
				return false;
		}
		for (colIter = 0; colIter < 9; colIter++)
		{
			if (colIter == col)
				continue;
			if (grid.getCellValue(row, colIter) == keyValue)
				return false;
		}

		if (!ThreeByThreeGridValid(row, col, keyValue))
			return false;
		return true;
	}

private:
	bool ThreeByThreeGridValid(int row, int col, int keyValue)
	{
		int rowIter, colIter;
		int s_start[3] = {0, 3, 6};
		int s_end[3] = {3, 6, 9};
		int s_r = int(row / 3);
		int s_c = int(col / 3);
		for (rowIter = s_start[s_r]; rowIter < s_end[s_r]; rowIter++)
		{
			for (colIter = s_start[s_c]; colIter < s_end[s_c]; colIter++)
			{
				if (rowIter == row && colIter == col)
				{
					continue;
				}

				if (grid.getCellValue(rowIter, colIter) == keyValue)
				{
					return false;
				}
			}
		}

		return true;
	}

private:
	bool gridSolved()
	{

		int flag;

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (grid.getCellValue(i, j) == 0)
					return false;

				flag = cellValueValid(i, j, grid.getCellValue(i, j));

				if (flag == 0)
				{
					return false;
				}
			}
		}

		return true;
	}

private:
	bool singleCellSolve()
	{
		statsIncrement();
		if (gridSolved())
			return true;
		int rowIter, colIter, keyValueIter;
		for (rowIter = 0; rowIter < 9; rowIter++)
		{
			for (colIter = 0; colIter < 9; colIter++)
			{
				if (grid.getCellValue(rowIter, colIter) == 0)
				{
					for (keyValueIter = 1; keyValueIter < 10; keyValueIter++)
					{

						if (cellValueValid(rowIter, colIter, keyValueIter))
						{
							grid.setCellValue(rowIter, colIter, keyValueIter);
							if (singleCellSolve())
								return true;
							grid.setCellValue(rowIter, colIter, 0);
						}
					}
					if (grid.getCellValue(rowIter, colIter) == 0)
						return false;
				}
			}
		}
		return false;
	}

private:
	void solve()
	{
		bool success = singleCellSolve();
		statsPrint();
		if (success)
		{
			cout << "Your puzzle has been solved!\n\n";
		}
		else
		{
			cout << "There is no correct answer for this puzzle :( \n";
		}
	}

private:
	void displayGrid()
	{
		grid.displayGrid();
	}

private:
	void statsIncrement()
	{
		recursiveCount++;
	}

public:
	void statsPrint()
	{
		cout << "\nThe singleCellSolve() function was recursively called " << recursiveCount << " times.\n";
	}
};

int main()
{
	int choice;
	do
	{
		SudokuSolver ss;
		cout << "Do you wish to solve another puzzle?" << endl;
		cout << "Enter 1 to continue..." << endl;
		cout << "Enter any other key to exit..." << endl;
		cin >> choice;
	} while (choice == 1);
	return 0;
}
