#include "sudoku.h"
#include <stdio.h>

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char*)(b + i) = (unsigned char)c;
		++i;
	}
	return (b);
}

int		ft_init_cell(t_sudo *cell, int x, int y, char v)
{
	cell->x = x;
	cell->y = y;
	cell->x1 = (cell->x / 3) * 3 + (cell->x + 1) % 3;
	cell->x2 = (cell->x / 3) * 3 + (cell->x + 2) % 3;
	cell->y1 = (cell->y / 3) * 3 + (cell->y + 1) % 3;
	cell->y2 = (cell->y / 3) * 3 + (cell->y + 2) % 3;
	ft_memset(cell->m, '0', 10);
	if (v == '.' || (v >= '1' && v <= '9'))
	{
		cell->v = v == '.' ? '0' : v;
		return (1);
	}
	else
		return (0);
}

int		ft_fill_grid(t_sudo **grid, char **argv)
{
	int		x;
	int		y;

	y = 0;
	while (++y < 10)
	{
		x = 0;
		if (!(grid[y - 1] = (t_sudo*)malloc(sizeof(t_sudo) * 9)))
			return (0);
		while (argv[y][x])
		{
			ft_init_cell(&grid[y - 1][x], x, y - 1, argv[y][x]);
			++x;
		}
		if (x != 9)
		{
			write(1, "check\n", 6);
			return (0);
		}
	}
	return (y == 10);
}

int		ft_check_value(t_sudo **grid, char c, int x, int y)
{
	int		i;

	i = 0;
	while (i < 9)
	{
		if (grid && grid && !(i == x && i == y))

		if (grid[i][x].v == c && i != y)
			return (0);
		if (grid[y][i].v == c && i != x)
			return (0);
		++i;
	}
	return ((c != grid[(y / 3) * 3 + (y + 1) % 3][(x / 3) * 3 + (x + 1) % 3].v)
		&& (c != grid[(y / 3) * 3 + (y + 2) % 3][(x / 3) * 3 + (x + 1) % 3].v)
		&& (c != grid[(y / 3) * 3 + (y + 1) % 3][(x / 3) * 3 + (x + 2) % 3].v)
		&& (c != grid[(y / 3) * 3 + (y + 2) % 3][(x / 3) * 3 + (x + 2) % 3].v));
}

void	ft_get_values(t_sudo **grid, t_sudo *s, int x, int y)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < 9)
	{
		s->m[grid[i][x].v - '0'] = grid[i][x].v;
		s->m[grid[y][i].v - '0'] = grid[y][i].v;
		++i;
	}
	s->m[grid[(y / 3) * 3 + (y + 1) % 3][(x / 3) * 3 + (x + 1) % 3].v - '0']
		= grid[(y / 3) * 3 + (y + 1) % 3][(x / 3) * 3 + (x + 1) % 3].v;
	s->m[grid[(y / 3) * 3 + (y + 2) % 3][(x / 3) * 3 + (x + 1) % 3].v - '0']
		= grid[(y / 3) * 3 + (y + 2) % 3][(x / 3) * 3 + (x + 1) % 3].v;
	s->m[grid[(y / 3) * 3 + (y + 1) % 3][(x / 3) * 3 + (x + 2) % 3].v - '0']
		= grid[(y / 3) * 3 + (y + 1) % 3][(x / 3) * 3 + (x + 2) % 3].v;
	s->m[grid[(y / 3) * 3 + (y + 2) % 3][(x / 3) * 3 + (x + 2) % 3].v - '0']
		= grid[(y / 3) * 3 + (y + 2) % 3][(x / 3) * 3 + (x + 2) % 3].v;
	i = -1;
	while (++i < 10)
		if (s->m[i] == '0')
			++count;
	s->prio = count;
}


int		ft_parse_grid(t_sudo **grid)
{
	int		x;
	int		y;

	y = -1;
	while (++y < 9)
	{
		x = -1;
		while (++x < 9)
		{
			if (grid[y][x].v != '0')
			{
				if (!(ft_check_value(grid, grid[y][x].v, x, y)))
					return (0);
				grid[y][x].prio = 42;
			}
			else
				ft_get_values(grid, &grid[y][x], x, y);
			if (!(x == 8 && y == 8))
				grid[y][x].next = &grid[y + (x == 8)][x < 8 ? x + 1 : 0];
			if (x != 0 && y != 0)
				grid[y][x].prev = &grid[y - (x == 0)][x > 0 ? x - 1 : 9];
		}
	}
	grid[0][0].prev = NULL;
	grid[8][8].next = NULL;
	return (1);
}

int		ft_parser(t_sudo **grid, char **argv)
{
	if (!(ft_fill_grid(grid, argv)))
		return (0);
	if (!(ft_parse_grid(grid)))
		return (0);
	return (1);
}
