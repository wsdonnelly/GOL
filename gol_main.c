#include "gol_header.h"

int main(int argc, char** argv)
{
	t_term_size t_size;
	char **gridA;
	char **gridB;
	char c = '$';

	get_term_size(&t_size);
	//printf("rows %d\n", t_size.rows);
	//printf("cols %d\n", t_size.cols);
	gridA = create_grid(&t_size);
	gridB = create_grid(&t_size);
	if (argc != 2)
	{
		printf("Enter a single parameter\n");
		return (0);
	}
	srand(time(0));
	rand_init_grid(argv[1], gridA, &t_size);
	//animate
	for (int i = 0; i < 1000; i++)
	{
		if (i % 2 == 0)
		{
			print_screen(gridA, &t_size, c);
			evolve(gridA, gridB, &t_size);
		}
		else
		{
			print_screen(gridB, &t_size, c);
			evolve(gridB, gridA, &t_size);
		}
		usleep(200000);
	}


	free_2D_arr(gridA, &t_size);
	free_2D_arr(gridB, &t_size);
	return (0);
}

