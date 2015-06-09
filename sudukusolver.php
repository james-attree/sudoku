<?php

set_time_limit(60);

class Coord
{
	public $x;
	public $y;
	public function __construct($x, $y)
	{
		$this->x = $x;
		$this->y = $y;
	}
}

class Grid
{
	private $_grid;
	private $_backtracks;
	public function __construct($input)
	{
		if (strlen($input) != 81)
		{
			die("Input is not long enough");
		}
		$n = 0;
		for ($i = 0; $i < 9; $i++)
		{
			for ($j = 0; $j < 9; $j++)
			{
				$this->_grid[$i][$j] = $input[$n];
				$n++;
			}
		}
	}
	public function print_grid()
	{
		for ($i = 0; $i < 9; $i++)
		{
			for ($j = 0; $j < 9; $j++)
			{
				echo $this->_grid[$i][$j] . " ";
			}
			echo '</br>';
		}
	}
	public function print_backtracks()
	{
		echo 'backtracks [' . $this->_backtracks . ']'; 
	}
	public function solve_sudoku()
	{
		$this->_solve($this->_find_next_unassigned_value(5,5));
	}
	private function _solve($c)
	{
		if ($this->_no_unassigned_values())
		{
			return true;
		}
		for ($num = 1; $num <= 9; $num++)
		{
			if ($this->_no_conflicts($c, $num))
			{
				$this->_grid[$c->x][$c->y] = $num;
				if ($this->_solve($this->_find_next_unassigned_value()))
				{
					return true;	
				}
				$this->_grid[$c->x][$c->y] = 0;
				$this->_backtracks += 1;
			}
		}
		return false;
	}
	private function _no_conflicts($c, $num)
	{
		for($i = 0; $i < 9; $i++)
		{
			// check row
			if ($this->_grid[$c->x][$i] == $num) return false;
			// check col
			if ($this->_grid[$i][$c->y] == $num) return false;
		}
		// check box
		if (!$this->_no_box_conflict($c, $num)) return false;
		return true;
	}
	private function _no_box_conflict($c, $num)
	{
		$start_row = 0;
		$start_col = 0;
		if ($c->x >= 3 && $c->x < 6) $start_row = 3;
		if ($c->x >= 6)				 $start_row = 6;
		if ($c->y >= 3 && $c->y < 6) $start_col = 3;
		if ($c->y >= 6)				 $start_col = 6;

		for ($i = $start_row; $i < $start_row + 3; $i++)
		{
			for ($j = $start_col; $j < $start_col + 3; $j++)
			{
				if($this->_grid[$i][$j] == $num) return false;
			}
		}
		return true;
	}
	private function _no_unassigned_values()
	{
		for ($i = 0; $i < 9; $i++)
		{
			for ($j = 0; $j < 9; $j++)
			{
				if ($this->_grid[$i][$j] == 0)
				{
					return false;
				}
			}
		}
		return true;
	}
	private function _find_next_unassigned_value($x = 0, $y = 0)
	{
		$flag = false;
		for ($i = 0; $i < 9; $i++)
		{
			for ($j = 0; $j < 9; $j++)
			{
				if (!$flag)
				{
					$i = $x;
					$j = $y;
					$flag = true;
				}
				if ($this->_grid[$i][$j] == 0)
				{
					return new Coord($i, $j);
				}
			}
		}
		return new Coord(0, 0);
	}
	private function _next_best_value($input = 0)
	{
		for ($i = 0; $i < 9; $i++)
		{
			
			for ($j = 0; $j < 9; $j++)
			{
				
			}
		}
	}
}
echo '<pre>';
$g = new Grid("000000000003600000070090200050007000000045700000100030001000068008500010090000400");
$g->print_grid();
$g->solve_sudoku();
echo '--</br>';
$g->print_grid();