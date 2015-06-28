#include "sudoku.h"

int main(int argc, char *argv[])
{
	char input[] = {
	'5','0','0','8','0','0','2','0','0',
	'0','3','0','9','0','1','0','0','0',
	'0','0','1','0','0','0','0','0','8',
	'8','2','0','0','0','9','0','6','0',
	'0','0','0','0','0','0','0','0','0',
	'0','9','0','1','0','0','0','0','3',
	'0','0','0','0','0','0','5','0','0',
	'0','0','0','5','0','0','0','1','0',
	'0','0','6','0','0','2','0','0','4'	
	};
	char input2[] = {
	'3','0','6','5','0','8','0','9','2',
	'0','0','0','0','0','0','0','0','0',
	'0','8','7','0','0','0','0','3','1',
	'0','0','3','0','1','0','0','8','0',
	'9','0','0','8','6','3','0','0','5',
	'0','5','0','0','9','0','6','0','0',
	'1','3','0','0','0','0','2','5','0',
	'0','0','0','0','0','0','0','7','4',
	'0','0','5','0','0','6','3','0','0'
	};
	char input3[] = {
	'0','0','0','0','0','0','0','0','0',
	'0','0','3','6','0','0','0','0','0',
	'0','7','0','0','9','0','2','0','0',
	'0','5','0','0','0','7','0','0','0',
	'0','0','0','0','4','5','7','0','0',
	'0','0','0','1','0','0','0','3','0',
	'0','0','1','0','0','0','0','6','8',
	'0','0','8','5','0','0','0','1','0',
	'0','9','0','0','0','0','4','0','0'
	};
	sudoku * s = SudokuInit(input3);
	coord * c = SudokuFindNextZero(s);
	assert(SudokuIsValid(s) == 1);
	SudokuPrint(s);
	SudokuSolve(s, c);
	SudokuPrint(s);
	printf("There were %d backtracks\n",s->backtracks);
	assert(SudokuIsValid(s) == 1);
	return 0;
}

void CoordInit(coord *c)
{
	c->x = 0;
	c->y = 0;
}

void CoordSet(coord *c, int x, int y)
{
	c->x = x;
	c->y = y;
}

sudoku * SudokuInit(char input[])
{
	sudoku * s = malloc(sizeof(sudoku));
	assert(s != NULL);
	int i, j;
	int k = 0;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			s->map[i][j] = (int)input[k] - 48;
			k++;	
		}
	}
	s->backtracks = 0;
	return s;	
}

void SudokuPrint(sudoku *s)
{
	printf("\n");
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			printf("[%d]",s->map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int SudokuSolve(sudoku *s, coord *c)
{
	if(SudokuNoUnassignedValues(s) == 1) return 1;
	int num;
	for(num = 1; num <= 9; num++)
	{
		if(SudokuNoConflict(s, c, num) == 1)
		{
			int tempx = c->x;
			int tempy = c->y;
			s->map[tempx][tempy] = num;
			coord * cp = SudokuFindNextZero(s);
			if(SudokuSolve(s, cp) == 1) 
			{
				free(cp);
				return 1;
			}
			free(cp);
			s->map[tempx][tempy] = 0;
			s->backtracks++;
		}
	}
	return 0;
}

coord * SudokuFindNextZero(sudoku *s)
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if (s->map[i][j] == 0)
			{
				coord * c = malloc(sizeof(coord));
				CoordSet(c, i, j);
				return c;
			}
		}
	}
	coord * c = malloc(sizeof(coord));
	CoordSet(c, 0, 0);
	return c;
}

int SudokuNoConflict(sudoku *s, coord *c, int num)
{
	// check the rows and columns
	int i, j;
	for(i = 0; i < 9; i++)
	{
		if(s->map[i][c->y] == num) return 0;
		if(s->map[c->x][i] == num) return 0;
	}
	// check the boxes
	int startx = 0;
	int starty = 0;
	if ((c->x >= 3) && (c->x < 6)) startx = 3;
	else if (c->x >= 6) startx = 6;
	if ((c->y >= 3) && (c->y < 6)) starty = 3;
	else if (c->y >= 6) starty = 6;
	for(i = startx; i < startx + 3; i++)
	{
		for(j = starty; j < starty + 3; j++)
		{
			if(s->map[i][j] == num) return 0;
		}
	}
	return 1;
}

int SudokuNoUnassignedValues(sudoku *s)
{
	int i, j;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(s->map[i][j] == 0) return 0;
		}
	}
	return 1;
}

int SudokuIsValid(sudoku *s)
{
	int n, i, j, count;
	for(n = 1; n <= 9; n++)
	{
		count = 0;
		for(i = 0; i < 9; i++)
		{
			count = 0;
			for(j = 0; j < 9; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;	
			}
			
		}
		// check first box
		count = 0;
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;
			}
		}
		// check second box
		count = 0;
		for(i = 0; i < 3; i++)
		{
			for(j = 3; j < 6; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;
			}
		}
		// check third box
		count = 0;
		for(i = 0; i < 3; i++)
		{
			for(j = 6; j < 9; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;
			}
		}
		// check fourth box
		count = 0;
		for(i = 3; i < 6; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;
			}
		}
		// check fifth box
		count = 0;
		for(i = 3; i < 6; i++)
		{
			for(j = 3; j < 6; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;
			}
		}
		// check sixth box
		count = 0;
		for(i = 3; i < 6; i++)
		{
			for(j = 6; j < 9; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;
			}
		}
		// check seventh box
		count = 0;
		for(i = 6; i < 9; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;
			}
		}
		// check eighth box
		count = 0;
		for(i = 6; i < 9; i++)
		{
			for(j = 3; j < 6; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;
			}
		}
		// check ninth box
		count = 0;
		for(i = 6; i < 9; i++)
		{
			for(j = 6; j < 9; j++)
			{
				if (s->map[i][j] == n) count++;
				if (count > 1) return 0;
			}
		}
	}
	return 1;
}
