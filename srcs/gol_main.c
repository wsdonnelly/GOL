#include "gol_header.h"

int main(int argc, char** argv)
{
	t_term_size t_size;
	char **gridA;
	char **gridB;
	char *c = "\u2580";

	get_term_size(&t_size);
	gridA = create_grid(&t_size);
	gridB = create_grid(&t_size);
	if (argc != 3)
	{
		printf("Enter a single density parameter followed by an init size parameter\n");
		return (0);
	}
	srand(time(0));
	rand_init_grid(argv[1], argv[2], gridA, &t_size);
	//animate
	for (int i = 0; i < 1000; i++)
	{
		if (i % 2 == 0)
		{
			print_screen(gridA, &t_size, c);
			//print_screen(gridA, &t_size);
			evolve(gridA, gridB, &t_size);
		}
		else
		{
			print_screen(gridA, &t_size, c);
			//print_screen(gridA, &t_size);
			evolve(gridB, gridA, &t_size);
		}
		usleep(200000);
	}


	free_2D_arr(gridA, &t_size);
	free_2D_arr(gridB, &t_size);
	return (0);
}

