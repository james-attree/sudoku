class Coord
{
    public int x;
    public int y;
    public Coord(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
}
class Sudoku
{
    private int[][] grid;
    private int backtracks;
    public Sudoku(String input)
    {
        this.grid = new int[9][9];
        this.backtracks = 0;
        if (this.assignGridFromInput(input))
        {
            this.solve(findNextZero());
            this.printGrid();
        }
    }
    private Boolean assignGridFromInput(String input)
    {
        if (input.length() != 81)
        {
            System.out.println("input string too short");
            return false;
        }
        int n = 1;
        String[] inputArray = input.split("");
        // Have to start n at 1, because splitting by nothing puts the first
        // element of the array to ''
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                grid[i][j] = Integer.parseInt(inputArray[n]);
                n++;
            }
        }
        return true;
    }
    private void printBacktracks()
    {
        System.out.println("Backtracks: " + this.backtracks);
    }
    private void printGrid()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                System.out.print(this.grid[i][j]);
            }
            System.out.print("\n");
        }
        System.out.println("-------");
    }
    private Boolean solve(Coord c)
    {
        this.printGrid();
        if (noUnassignedValues())
        {
            return true;
        }
        for (int num = 1; num <= 9; num++)
        {
            if (noConflicts(c, num))
            {
                this.grid[c.x][c.y] = num;
                if (solve(findNextZero()))
                {
                    return true;
                }
                this.grid[c.x][c.y] = 0;
                backtracks++;
            }
        }
        return false;
    }
    private Boolean noConflicts(Coord c, int num)
        {
            for (int i = 0; i < 9; i++)
            {
                // check row
                if (this.grid[c.x][i] == num) return false;
                // check col
                if (this.grid[i][c.y] == num) return false;
            }
            // check box
            if (!this.noBoxConflict(c, num)) return false;
            return true;
        }
    private Boolean noBoxConflict(Coord c, int num)
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
                    if (this.grid[i][j] == num) return false;
                }
            }
            return true;
        }
    private Boolean noUnassignedValues()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (this.grid[i][j] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
    private Coord findNextZero()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (this.grid[i][j] == 0)
                    return new Coord(i, j);
            }
        }
        return new Coord(0, 0);
    }
}
public class SudokuSolver
{
     public static void main(String[] args){
        // Can change the program to input string from Command Line, or from other means.
        String input = "000000000003600000070090200050007000000045700000100030001000068008500010090000400";
        //String input = "040905080601040302050000070700402001030000060800306007080000020905030604020701090";
        Sudoku s = new Sudoku(input);
     }
}
