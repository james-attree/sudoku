//
//  Sudoku.swift
//  SudokuSolver
//
//  Created by James Attree on 07/06/2015.
//  Copyright (c) 2015 Hawkapps. All rights reserved.
//

import Foundation

class Coord
{
    internal var x : Int;
    internal var y : Int;
    init(CoordX x: Int, CoordY y: Int)
    {
        self.x = x;
        self.y = y;
    }
}

class Sudoku
{
    private var grid : Array<Array<Int>>;
    private var backtracks : Int;
    init()
    {
        self.grid = Array<Array<Int>>();
        self.backtracks = 0;
        for x in 0...8 {
            grid.append(Array(count: 9, repeatedValue: Int()));
        }
        self.print_grid();
        self.solve(Coord: find_next_zero());
        println("");
        self.print_grid();
    }
    internal func print_grid() -> Void
    {
        var n: Int = 0;
        for x in 0...8
        {
            for y in 0...8
            {
                print("[" + String(self.grid[x][y]) + "]");
                n++;
            }
            print("\n");
        }
    }
    internal func solve(Coord c : Coord) -> Bool
    {
        if (no_zeros()) { return true; }
        
        for num in 1...9
        {
            if (no_conflicts(inputCoord: c, numberToCheck: num))
            {
                self.grid[c.x][c.y] = num;
                if (solve(Coord: find_next_zero())) { return true; }
                self.grid[c.x][c.y] = 0;
                self.backtracks++;
            }
        }
        return false;
    }
    internal func no_conflicts(inputCoord c : Coord, numberToCheck num: Int) -> Bool
    {
        for x in 0...8
        {
            if (self.grid[x][c.y] == num) { return false; }
            if (self.grid[c.x][x] == num) { return false; }
        }
        if (!no_box_conflict(inputCoord: c, numberToCheck: num)) { return false; }
        return true;
    }
    internal func no_box_conflict(inputCoord c : Coord, numberToCheck num : Int) -> Bool
    {
        var startRow : Int = 0;
        var startCol : Int = 0;
        if (c.x >= 3 && c.x < 6) { startRow = 3; }
        if (c.x >= 6) { startRow = 6; }
        if (c.y >= 3 && c.y < 6) { startCol = 3; }
        if (c.y >= 6) { startCol = 6; }
        for x in startRow...startRow+2
        {
            for y in startCol...startCol+2
            {
                if (self.grid[x][y] == num)
                {
                    return false;
                }
            }
        }
        return true;
    }
    internal func no_zeros() -> Bool
    {
        for x in 0...8
        {
            for y in 0...8
            {
                if (self.grid[x][y] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
    internal func find_next_zero() -> Coord
    {
        for x in 0...8
        {
            for y in 0...8
            {
                if (self.grid[x][y] == 0)
                {
                    return Coord(CoordX: x, CoordY: y);
                }
            }
        }
        return Coord(CoordX: 0, CoordY: 0);
    }
}
