
#include <iostream> //input output stream
#include <ctype.h> //to use isdigit function
#include <fstream> //file stream
/* has the capabilities of both ofstream and ifstream
meaning it can create files, write information to files,
and read information from files :)*/

#define BOX 9

using namespace std;
/*use of name space:
as the same name can't be given to multiple variables, functions,
classes, etc. in the same scope
namespace overcomes this
allows for the scope to be divided into subscopes with their
own names*/

void importfile(int grid[BOX][BOX]){
	char obj;

	fstream afile;
	afile.open("sudoku.txt", ios::in); //hmm fstream is kind of dangerous. you can read and write in the file

	//store the items in the grid 1 row a time
	for (int row = 0; row < BOX; row++) {
		for (int col = 0; col < BOX; col++) {
			afile >> obj;
			//obj = isdigit(obj); why can't I do this?
			if (isdigit(obj)) {
				grid[row][col] = obj - '0'; //minus zero because it is using ascii values
			}
		}
	}
	 afile.close(); //it automatically closes the file? but it is good practice to close it anyway
}

void print(int grid[BOX][BOX]) {
	cout << "   === === ===  === === ===  === === ===" << endl;
	for (int row = 0; row < BOX; row++) {
		for (int col = 0; col < BOX; col++) {
			if (col == 0 || col == 3 || col == 6) {
				cout << " || ";
			}
			if (col == 1 || col == 2 || col == 4 || col == 5 || col == 7 || col ==8) {
				cout << " | ";
			}
			if (grid[row][col] == 0) {
				cout << " ";
				if (col == 8) {
					cout << " ||";
				}
			}
			else {
				cout << grid[row][col];
				if (col == 8) {
					cout << " ||";
				}
			}
		}
		if (row == 2 || row == 5) {
			cout << endl;
			cout << "   === === ===  === === ===  === === ===";
		}
		if (row == 0 || row == 1 || row == 3 || row == 4 || row == 6 || row == 7) {
			cout << endl;
			cout << "   --- --- ---  --- --- ---  --- --- ---";
		}
		cout << endl;
	}
	cout << "   === === ===  === === ===  === === ===" << endl;
}

int checkrow(int grid[BOX][BOX],int row, int n) {
	// go through each column in that row checking if this number already exists in the row
	for (int col = 0; col < BOX; col++) {
		if (grid[row][col] == n) {
			return 1;
		}
	}
	return 0;
}

int checkcol(int grid[BOX][BOX], int col, int n) {
	// go through each row in that col checking if this number already exists in the col
	for (int row = 0; row < BOX; row++) {
		if (grid[row][col] == n) {
			return 1;
		}
	}
	return 0;
}

int checkbox(int grid[BOX][BOX], int row, int col, int n) {
	for (int irow = 0; irow < 3; irow++) {
		for (int icol = 0; icol < 3; icol++) {
			if (grid[irow + row][icol + col] == n) {
				return 1;
			}
		}
	}
	return 0;
}

int empty(int grid[BOX][BOX], int& row, int& col) {
	/* passing the address here to modify the value ;)*/
	for (row = 0; row < BOX; row++) {
		for (col = 0; col < BOX; col++) {
			if (grid[row][col] == 0) {
				return 1;
			}
		}
	}
	return 0;
	//function goes through one cell at a time checking if it is empty or not
}

int check(int grid[BOX][BOX], int row, int col, int n) {
	return (!checkbox(grid, row - row % 3, col - col % 3, n) && !checkrow(grid, row, n) && !checkcol(grid, col, n));
}

int solve(int grid[BOX][BOX]) {
	int row, col;
	if (!empty(grid,row, col)) {
		return 1; //if there aren't any empty cells left the sudoku is solved
	}
	for (int n = 1; n <= 9; n++) {
		if (check(grid, row, col, n)) {
			grid[row][col] = n;
			//this is a recursive function (calling a function in itself)
			if (solve(grid)) {
				return 1;
			}
			/*recursion makes the program cleaner and more elegant. However, if the
			speed of the program is vital, then recursion should be
			avoided as it uses more memory and is generally slow, use loops instead.
			the main advantage of recursion is that for problems like tree traveral the algorithim becomes easier.
			who would have known that chaos theory and selfsimilarity using a capacitor would come in handy*/
			grid[row][col] = 0;
		}

	}
	return 0;
	//non-recursive method// nvm can't be asked to try this
}



//c++ has a grid? wow, I love c++. so much better than c
// hmm shouldn't use global variables so that I can increase clarity
int main(){

	int grid[BOX][BOX] {0};

	cout << "The Sudoku Problem:" << endl;
//	fileortype(); could possibly ask for the option to insert the values of the
	importfile(grid);
	// checker(grid); we could possibly write some code to check if the grid is valid or has any repititions right from the start
	print(grid);

	// Solving Problem
	if (solve(grid)) {
		cout << "Solved" << endl;
		print(grid);
	}
	else {
		cout << "Cannot solve" << endl;
	}

	return 0;
}
