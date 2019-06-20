#ifndef SUDOKU_H
# define SUDOKU_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_sudo
{
	int				x;
	int				y;
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	char			v;
	char			m[10];
	int				prio;
	struct s_sudo	*next;
	struct s_sudo	*prev;
}					t_sudo;

int					ft_parser(t_sudo **grid, char **argv);
int					ft_solver(t_sudo **grid, t_sudo *list);
void				ft_print_grid(t_sudo **grid);
int					ft_is_valid(t_sudo **grid, t_sudo *cell, char c);

#endif