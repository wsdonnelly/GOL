#include "gol_header.h"

void get_term_size(t_term_size *t_size)
{
	struct winsize	w;

	ioctl(1 , TIOCGWINSZ, &w);
	t_size->rows = w.ws_row;
	t_size->cols = w.ws_col;
}

char **create_grid(t_term_size *t_size)
{
	char **grid;

	grid = (char **)malloc(sizeof(char *) * t_size->rows);
	for (int i = 0; i < t_size->rows; i++)
		grid[i] = (char *)malloc(sizeof(char) * t_size->cols);
	return (grid);
}

void	free_2D_arr(char **grid, t_term_size *t_size)
{
	for (int i = 0; i < t_size->rows; i++)
		free (grid[i]);
	free (grid);
}

//attempt 10th of size of term
void rand_init_grid(char *density, char *init_size, char **gridA, t_term_size *t_size)
{
	int num;
	int percent;
	int shift;
	int i_start;
	int i_stop;
	int j_start;
	int j_stop;

	shift = atoi(init_size) * 2;
	percent = atoi(density);
	i_start = (t_size->rows / 2) - (t_size->rows / shift);
	i_stop = (t_size->rows / 2) + (t_size->rows / shift);
	j_start = (t_size->cols/ 2) - (t_size->cols / shift);
	j_stop = (t_size->cols/ 2) + (t_size->cols / shift);

	for (int i = i_start; i < i_stop; i++)
		for (int j = j_start; j < j_stop; j++)
		{
			num = rand() % 100;
			if (num <= percent)
				gridA[i][j] = 1;
			else
				gridA[i][j] = 0;
		}
}
//color version
//void print_screen(char **grid, t_term_size *t_size, char c)
void print_screen(char **grid, t_term_size *t_size, char *c )
//void	print_screen(char **grid, t_term_size *t_size)
{
	printf("\033[H");

	for (int i = 0; i < t_size->rows; i++)
	{
		for (int j = 0; j < t_size->cols; j++)
		{
			if (grid[i][j] == 1)
			{
				
				
				if (num_neighbors(grid, i, j, t_size) == 1)
				{
					printf("\033[32m");
					printf("%s", c);
					//printf("\u2588");
				}
				else if (num_neighbors(grid, i, j, t_size) == 2)
				{
					printf("\033[36m");
					printf("%s", c);
					//printf("\u2588");
				}
				else if (num_neighbors(grid, i, j, t_size) == 3)
				{
					printf("\033[35m");
					printf("%s", c);
					//printf("\u2588");
				}
				else if (num_neighbors(grid, i, j, t_size) == 4)
				{
					printf("\033[34m");
					printf("%s", c);
					//printf("\u2588");
				}
				else if (num_neighbors(grid, i, j, t_size) == 5)
				{
					printf("\033[33m");
					printf("%s", c);
					//printf("\u2588");
				}
				else if (num_neighbors(grid, i, j, t_size) == 6)
				{
					printf("\033[31m");
					printf("%s", c);
					//printf("\u2588");
				}
				else if (num_neighbors(grid, i, j, t_size) == 7)
				{
					printf("\033[37m");
					printf("%s", c);
					//printf("\u2588");
				}
				else if (num_neighbors(grid, i, j, t_size) == 8)
				{
					printf("\033[37m");
					printf("%s", c);
					//printf("\u2588");
				}
	
			}
			else
				printf(" ");
		}
		printf("\033[E");
	}
	fflush(stdout);
}

/* B&W version
void print_screen(char **grid, t_term_size *t_size, char c)
{
	printf("\033[H");

	for (int i = 0; i < t_size->rows; i++)
	{
		for (int j = 0; j < t_size->cols; j++)
		{
			if (grid[i][j] == 1)
				printf("%c", c);
			else
				printf(" ");
		}
		printf("\033[E");
	}
	fflush(stdout);
}
*/
/*

Any live cell with two or three live neighbours survives.
Any dead cell with three live neighbours becomes a live cell.
All other live cells die in the next generation. Similarly, all other dead cells stay dead.
*/
void evolve(char **grid1, char **grid2, t_term_size *t_size)
{
	for (int i = 0; i < t_size->rows; i++)
		for (int j = 0; j < t_size->cols; j++)
		{
			if (grid1[i][j] == 1 && (num_neighbors(grid1, i, j, t_size) == 2 || num_neighbors(grid1, i, j, t_size) == 3))
				grid2[i][j] = 1;
			else if (grid1[i][j] == 0 && num_neighbors(grid1, i, j, t_size) == 3)
			//else if (grid1[i][j] == 0 && (num_neighbors(grid1, i, j, t_size) == 3 || num_neighbors(grid1, i, j, t_size) == 6)) //HIGHLIFE
				grid2[i][j] = 1;
			else
				grid2[i][j] = 0;
		}
}

//non pac man space
int num_neighbors(char **grid, int i , int j, t_term_size *t_size)
{
	int count = 0;

	if (i - 1 >= 0 && j - 1 >= 0)
		if (grid[i - 1][j - 1] == 1)
			count++;
	if (i - 1 >= 0)
		if (grid[i - 1][j] == 1 )
			count++;
	if (i - 1 >= 0 && j + 1 < t_size->cols)
		if (grid[i - 1][j + 1] == 1 )
			count++;
	if (i + 1 < t_size->rows && j - 1 >= 0 )
		if (grid[i + 1][j - 1] == 1)
			count++;
	if (i + 1 < t_size->rows)
		if (grid[i + 1][j] == 1)
			count++;
	if (i + 1 < t_size->rows && j + 1 < t_size->cols)
		if (grid[i + 1][j + 1] == 1)
			count++;
	if (j - 1 >= 0)
		if (grid[i][j - 1] == 1)
			count++;
	if (j + 1 < t_size->cols)
		if (grid[i][j + 1] == 1)
			count++;
	return (count);
}
