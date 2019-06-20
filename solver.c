#include "sudoku.h"
#include <stdio.h>

int		ft_is_valid(t_sudo **grid, t_sudo *cell, char c)
{
	int i;

	i = 0;
	while (i < 9)
	{
		if (grid[cell->y][i].v == c && i != cell->x)
			return 0;
		if (grid[i][cell->x].v == c && i != cell->y)
			return (0);
		++i;
	}
	return ((c != grid[cell->y1][cell->x1].v)
		&& (c != grid[cell->y2][cell->x1].v)
		&& (c != grid[cell->y1][cell->x2].v)
		&& (c != grid[cell->y2][cell->x2].v));
}

int		ft_solver(t_sudo **grid, t_sudo *cell)
{
	char	c;

	c = '1';
	if (cell->v != '0')
		return (1);
	while (c <= '9')
	{
		if (ft_is_valid(grid, cell, c))
		{
			cell->v = c;
			if (ft_solver(grid, cell->next))
				return (1);
			cell->v = '0';
		}
		++c;
	}
	return (0);
}
