#include "philo.h"

void	usage(void)
{
	printf("Usage: ./philo\n");
	printf("number_of_philosophers < 2\n");
	printf("time_to_die < 60\n");
	printf("time_to_eat < 60\n");
	printf("time_to_sleep < 60\n");
	printf("[number_of_times_each_philosopher_must_eat] < 1\n");
	exit(1);
}

void	parsing(int argc, char **argv, t_table *table)
{
	table->philo_num = atoi(argv[1]);
	table->time_to_die = atoi(argv[2]);
	table->time_to_eat = atoi(argv[3]);
	table->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		table->eat_times = atoi(argv[5]);
	else
		table->eat_times = -1;
	if (table->philo_num < 2 || table->philo_num > 200 || table->time_to_die < 60 || table->time_to_eat < 60 || table->time_to_sleep < 60 || (table->eat_times < 1 && table->eat_times != -1))
		usage();
}

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
