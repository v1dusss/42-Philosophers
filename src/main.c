#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		usage();
	parsing(argc, argv, &table);
	printf("philo_num: %d\n", table.philo_num);
	printf("time_to_die: %d\n", table.time_to_die);
	printf("time_to_eat: %d\n", table.time_to_eat);
	printf("time_to_sleep: %d\n", table.time_to_sleep);
	if (table.eat_times != -1)
		printf("eat_times: %d\n", table.eat_times);
	printf("\033[1;32mParsing is done! \033[0m\n");
	return (0);
}
