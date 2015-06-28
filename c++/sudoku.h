#ifndef sudoku_h
#define sudoku_h

#include <iostream>

using namespace std;

class Coord{
public:
	int x;
	int y;
	Coord(int x, int y);
};

class Sudoku{
private:
	int map[9][9];
public:
	int backtracks;
	Sudoku(char input[]);
	void Print();
	bool Solve(Coord *c);
	Coord * FindNextZero();
	bool NoConflict(Coord *c, int num);
	bool NoUnassignedValues();
	bool IsValid();
};

#endif