// Author :: <Hitesh_Saini> BTECH CST
#include<bits/stdc++.h>
using namespace std;


void printBoard(vector<vector<int>>& sudoku) {
	for (vector<int>& rows : sudoku) {
		for (int& number : rows)
			cout << number << ' ';
		cout << '\n';
	}
}


vector<int> possible_entries(vector<vector<int>>& sudoku, int x, int y) { // O(1)
	int i, j;
	vector<int> present(10), possible;

	for (i = 0; i < 9; i++) // xth row
		if (sudoku[x][i] != 0)
			present[sudoku[x][i]] = 1;

	for (j = 0; j < 9; j++) // yth column
		if (sudoku[j][y] != 0)
			present[sudoku[j][y]] = 1;

	int sqx = (x/3)*3, sqy = (y/3)*3;

	for (i = 0; i < 3; i++) 
		for (j = 0; j < 3; j++) // for 3*3 squares
			present[sudoku[sqx+i][sqy+j]] = 1;

	for (i = 1; i <= 9; i++)
		if (!present[i])
			possible.push_back(i);

	return possible;
}


bool solve(vector<vector<int>>& sudoku, int x = 0, int y = 0){
	if (x == 8 && y == 9)
		return true;

	if (y == 9) {
		x += 1;
		y = 0;
	}

	if (sudoku[x][y] != 0) // if sudoku[x][y] is already occupied we skip
		return solve(sudoku, x, y+1);

	vector<int> possibleValues = possible_entries(sudoku, x, y); // possible values that cell (x, y) can have

	for (int n : possibleValues) {
		sudoku[x][y] = n;

		if (solve(sudoku, x, y + 1))
			return true;

		sudoku[x][y] = 0; // back-tracking if none of possible values solves sudoku
	}
	return false;
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	char ask;

	cout << "Wanna enter entries for sudoku yourself? (Y/N) : ";
	cin >> ask;

	cout << '\n';

	if (ask == 'Y' || ask == 'y') {
		vector<vector<int>> sudoku(9, vector<int>(9));

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
					cin >> sudoku[i][j];

		cout << "Original sudoku:: \n";
		printBoard(sudoku);

		cout << '\n';

		if (solve(sudoku)) {
			cout << "SUCCESSFULLY SOLVED!\n";
			printBoard(sudoku);
		} else
			cout << "No solution Exists!\n";

	} else {
		vector<vector<int>> sudoku = {
			{0,1,0, 0,7,8, 0,0,4},
			{0,8,0, 0,4,0, 9,0,0},
			{0,0,5, 6,0,0, 0,1,0},

			{1,0,0, 0,6,0, 0,0,5},
			{0,4,0, 9,1,5, 0,7,2},
			{0,6,7, 0,8,0, 4,0,0},

			{8,0,0, 3,0,0, 1,0,0},
			{0,7,0, 8,9,0, 0,2,3},
			{0,0,0, 0,0,4, 0,0,0},

		};

		cout << "Original sudoku:: \n";
		printBoard(sudoku);
		cout << '\n';

		if (solve(sudoku)) {
			cout << "SUCCESFULLY SOLVED!\n";
			printBoard(sudoku);
		}
		else 
			cout << "No solution exists!";
	}
    
    return 0;
}
