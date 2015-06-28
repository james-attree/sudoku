using System;
using System.Diagnostics;
	class Coord
    {
        public int x { get; set; }
        public int y { get; set; }
        public Coord(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }
    class Grid
    {
        
        private int[,] m_grid;
        private int m_backtracks = 0;
        public Grid(string input)
        {
            if (input.Length != 81)
            {
                throw new Exception("Input is not long enough [" + input.Length + "]");
            }
            m_grid = new int[9, 9];
            int n = 0;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    m_grid[i, j] = Convert.ToInt32(Convert.ToString(input[n]));
                    n++;
                }
            }
        }
        public int num(int x, int y)
        {
            return this.m_grid[x, y];
        }
        public void Print()
        {
            Console.WriteLine("---");
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    Console.Write(m_grid[i, j] + " ");
                }
                Console.Write("\n");
            }
        }
        public void PrintBacktracks()
        {
            Console.WriteLine("Backtracks: [" + m_backtracks + "]");
        }
        public void SolveSudoku()
        {
            Solve(findNextUnassignedValue());
        }
        private bool Solve(Coord c)
        {
            //this.Print();
            if (noUnassignedValues())
            {
                return true;
            }
            for (int num = 1; num <= 9; num++)
            {
                if (NoConflicts(c, num))
                {
                    m_grid[c.x, c.y] = num;
                    if (Solve(findNextUnassignedValue()))
                    {
                        return true;
                    }
                    m_grid[c.x, c.y] = 0;
                    m_backtracks += 1;
                }
            }
            return false;
        }
        private bool NoConflicts(Coord c, int num)
        {
            for (int i = 0; i < 9; i++)
            {
                // check row
                if (m_grid[c.x, i] == num) return false;
                // check col
                if (m_grid[i, c.y] == num) return false;
            }
            // check box
            if (!NoBoxConflict(c, num)) return false;
            return true;
        }
        private bool NoBoxConflict(Coord c, int num)
        {
            int startRow = 0;
            int startCol = 0;
            if (c.x >= 3 && c.x < 6) startRow = 3;
            if (c.x >= 6) startRow = 6;
            if (c.y >= 3 && c.y < 6) startCol = 3;
            if (c.y >= 6) startCol = 6;

            for (int i = startRow; i < startRow + 3; i++)
            {
                for (int j = startCol; j < startCol + 3; j++)
                {
                    if (m_grid[i, j] == num) return false;
                }
            }
            return true;
        }
        private bool noUnassignedValues()
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (m_grid[i, j] == 0)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        private Coord findNextUnassignedValue()
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (m_grid[i, j] == 0)
                    {
                        return new Coord(i, j);
                    }
                }
            }
            return new Coord(0, 0);
        }
    }
	class Sudoku
    {
        public static void Main()
        {
			Stopwatch watch = Stopwatch.StartNew();
            //Grid g = new Grid("306508092000000000087000031003010080900863005050090600130000250000000074005006300");
			//Grid g = new Grid("000000000003600000070090200050007000000045700000100030001000068008500010090000400");
			Grid g = new Grid("000000000000000000000000000000000000000000000000000000000000000000000000000000000");
            g.Print();
            g.SolveSudoku();
			watch.Stop();
            g.Print();
            g.PrintBacktracks();
			Console.WriteLine("Time taken: " + watch.ElapsedMilliseconds.ToString() + "ms.");
        }
    }