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

void rand_init_grid(char *argv, char **gridA, t_term_size *t_size)
{
	int num;
	int percent;

	percent = atoi(argv);
	for (int i = 0; i < t_size->rows; i++)
		for (int j = 0; j < t_size->cols; j++)
		{
			num = rand() % 100;
			if (num <= percent)
				gridA[i][j] = 1;
			else
				gridA[i][j] = 0;
		}
}

void print_screen(char **grid, t_term_size *t_size, char c)
{
	//printf("\033[2J");
	printf("\033[H");

	for (int i = 0; i < t_size->rows; i++)
	{
		for (int j = 0; j < t_size->cols; j++)
		{
			if (grid[i][j] == 1)
				printf("%c", c);
				//printf("\033[07m  \033[m");
			else
				printf(" ");
		}
		//printf("\n");
		printf("\033[E");
	}
	fflush(stdout);
}


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

/*
//PACMANspace
int num_neighbors(char **grid, int i , int j, t_term_size *t_size)
{
	int count = 0;

	if (i == 0 && j == 0) //top left corner
	{
		if (grid[t_size->rows - 1][t_size->cols - 1] == 1)
			count++;
		if (grid[t_size->rows - 1][j] == 1)
			count++
		if (grid[t_size->rows - 1][j + 1] == 1)
			count++;
		if (grid[i][t_size->cols - 1] == 1)
			count++;
		if (grid[i][j + 1] == 1)
			count++;
		if (grid[i + 1][t_size->cols - 1] == 1)
			count++;
		if (grid[i + 1][j] == 1)
			count++;
		if (grid[i + 1][j + 1] == 1)
			count++;
	}
	else if (i == 0 && j == t_size->cols - 1) //top right corner
	{
		if(grid[t_size->rows - 1][j - 1] == 1)
			count++;
		if(grid[t_size->rows - 1][j] == 1)
			count++;
		if(grid[t_size->rows - 1][0] == 1)
			count++;
		if(grid[i][j - 1] == 1)
			count++;
		if(grid[i][0] == 1)
			count++;
		if(grid[i + 1][j - 1] == 1)
			count++;
		if(grid[i + 1][j] == 1)
			count++;
		if(grid[i + 1][0] == 1)
			count++;
	}
	else if (i == t_size->rows - 1) && j == 0) //bottom left corner
	{
		if (grid[][] == 1)
			count++;
		if (grid[][] == 1)
			count++;
		if (grid[][] == 1)
			count++;
		if (grid[][] == 1)
			count++;
		if (grid[][] == 1)
			count++;
		if (grid[][] == 1)
			count++;
		if (grid[][] == 1)
			count++;
		if (grid[][] == 1)
			count++;
	}

	return (count);
}
*/