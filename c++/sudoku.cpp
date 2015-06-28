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
	Sudoku *s = new Sudoku(input);
	if (!s->IsValid())
	{
		cout << "This is not a valid input!" << endl;
		return 1;
	}
	Coord *c = s->FindNextZero();
	s->Print();
	s->Solve(c);
	s->Print();
	cout << "There were " << s->backtracks << " backtracks." << endl;
	if (!s->IsValid())
	{
		cout << "This is not a valid solution!" << endl;
		return 1;
	}
	delete(s);
	delete(c);
	return 0;
}

Coord::Coord(int x, int y)
{
	this->x = x;
	this->y = y;
}

Sudoku::Sudoku(char input[])
{
	int i, j;
	int k = 0;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			this->map[i][j] = (int)input[k] - 48;
			k++;
		}
	}
	this->backtracks = 0;
}

void Sudoku::Print()
{
	cout << endl;
	int i, j;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			cout << "[" << this->map[i][j] << "]";
		}
		cout << endl;
	}
	cout << endl;
}

bool Sudoku::Solve(Coord *c)
{
	if(this->NoUnassignedValues()) return true;
	int num;
	for(num = 1; num <= 9; num++)
	{
		if(this->NoConflict(c, num))
		{
			int tempx = c->x;
			int tempy = c->y;
			this->map[tempx][tempy] = num;
			Coord *cp = FindNextZero();
			if(Solve(cp))
			{
				delete(cp);
				return true;
			}
			delete(cp);
			this->map[tempx][tempy] = 0;
			this->backtracks++;
		}
	}
	return false;
}

Coord * Sudoku::FindNextZero()
{
	int i, j;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(this->map[i][j] == 0)
			{
				Coord *c = new Coord(i, j);
				return c;
			}
		}
	}
	Coord *c = new Coord(0, 0);
	return c;
}

bool Sudoku::NoConflict(Coord *c, int num)
{
// check the rows and columns
	int i, j;
	for(i = 0; i < 9; i++)
	{
		if(this->map[i][c->y] == num) return false;
		if(this->map[c->x][i] == num) return false;
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
			if(this->map[i][j] == num) return false;
		}
	}
	return true;	
}

bool Sudoku::NoUnassignedValues()
{
	int i, j;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(this->map[i][j] == 0) return false;
		}
	}
	return true;
}

bool Sudoku::IsValid()
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
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;	
			}
			
		}
		// check first box
		count = 0;
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;
			}
		}
		// check second box
		count = 0;
		for(i = 0; i < 3; i++)
		{
			for(j = 3; j < 6; j++)
			{
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;
			}
		}
		// check third box
		count = 0;
		for(i = 0; i < 3; i++)
		{
			for(j = 6; j < 9; j++)
			{
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;
			}
		}
		// check fourth box
		count = 0;
		for(i = 3; i < 6; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;
			}
		}
		// check fifth box
		count = 0;
		for(i = 3; i < 6; i++)
		{
			for(j = 3; j < 6; j++)
			{
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;
			}
		}
		// check sixth box
		count = 0;
		for(i = 3; i < 6; i++)
		{
			for(j = 6; j < 9; j++)
			{
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;
			}
		}
		// check seventh box
		count = 0;
		for(i = 6; i < 9; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;
			}
		}
		// check eighth box
		count = 0;
		for(i = 6; i < 9; i++)
		{
			for(j = 3; j < 6; j++)
			{
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;
			}
		}
		// check ninth box
		count = 0;
		for(i = 6; i < 9; i++)
		{
			for(j = 6; j < 9; j++)
			{
				if (this->map[i][j] == n) count++;
				if (count > 1) return false;
			}
		}
	}
	return true;
}