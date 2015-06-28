#ifndef sudoku_h
#define sudoku_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
	int x;
	int y;
} coord;

typedef struct {
	int map[9][9];
	int backtracks;
} sudoku;

void CoordInit(coord *c);
void CoordSet(coord *c, int x, int y);
sudoku * SudokuInit(char input[]);
void SudokuPrint(sudoku *s);
int SudokuSolve(sudoku *s, coord *c);
coord * SudokuFindNextZero(sudoku *s);
int SudokuNoConflict(sudoku *s, coord *c, int num);
int SudokuNoUnassignedValues(sudoku *s);
int SudokuIsValid(sudoku *s);

#endif	
