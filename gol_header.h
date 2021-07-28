#ifndef GOL_H
# define GOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>

typedef struct	s_term_size
{
	int	rows;
	int	cols;
}	t_term_size;


void	get_term_size(t_term_size *t_size);
char	**create_grid(t_term_size *t_size);
void	free_2D_arr(char **grid, t_term_size *t_size);
void	rand_init_grid(char *argv, char **gridA, t_term_size *t_size);
void	print_screen(char **grid, t_term_size *t_size, char c);
void	evolve(char **gridA, char **gridB, t_term_size *t_size);
int		num_neighbors(char **grid, int i , int j, t_term_size *t_size);

#endif