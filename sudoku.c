#include "sudoku.h"

void	ft_print_grid(t_sudo **grid)
{
	int		y;
	int		x;
	char	buf[18];

	y = 0;
	while (y < 9)
	{
		x = 0;
		while (x < 17)
		{
			buf[x] = x % 2 ? ' ' : grid[y][x / 2].v;
			++x;
		}
		buf[x] = '\n';
		write(1, buf, 18);
		++y;
	}
}

/*
*/
void	ft_insert(t_sudo **list, t_sudo *new)
{
	t_sudo	*curr;

	if (!(*list))
		*list = new;
	else if (new->prio <= (*list)->prio)
	{
		new->next = *list;
		(*list)->prev = new;
		*list = new;
	}
	else
	{
		curr = *list;
		while (curr->next && new->prio > curr->next->prio)
			curr = curr->next;
		new->next = curr->next;
		if (new->next)
			new->next->prev = new;
		curr->next = new;
		new->prev = curr;
	}
}

void	ft_sort_list(t_sudo **list)
{
	t_sudo	*tmp;
	t_sudo	*curr;
	t_sudo	*next;

	tmp = NULL;
	curr = *list;
	while (curr)
	{
		next = curr->next;
		curr->prev = NULL;
		curr->next = NULL;
		ft_insert(&tmp, curr);
		curr = next;
	}
	*list = tmp;
}

void	ft_free_grid(t_sudo **grid)
{
	int		i;

	i = 0;
	while (i < 9)
	{
		free(grid[i]);
		++i;
	}
	free(grid);
}

int		main(int argc, char **argv)
{
	t_sudo	**grid;
	t_sudo	*list;

	if (argc == 10)
	{
		if (!(grid = (t_sudo**)malloc(sizeof(t_sudo*) * 9)))
			return (0);
		if (!(ft_parser(grid, argv)))
		{
			write(1, "Error : Invalid grid\n", 21);
			return (0);
		}
		list = &grid[0][0];
		ft_sort_list(&list);
		if (ft_solver(grid, list))
			ft_print_grid(grid);
		ft_free_grid(grid);
	}
	else
		write(1, "Map error : wrong number of lines\n", 34);
	return (0);
}

/*
		char	c;
		while (list)
		{
			write(1, &list->v, 1);
			write(1, ", ", 2);
			c = list->prio + '0';
			write(1, &c, 1);
			write(1, "\n", 1);
			list = list->next;
		}
*/