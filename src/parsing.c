#include "philo.h"

void	usage(void)
{
	printf("Usage: ./philo\n");
	printf("* number_of_philosophers > 2\n");
	printf("* time_to_die > 60\n");
	printf("* time_to_eat > 60\n");
	printf("* time_to_sleep > 60\n");
	printf("* [number_of_times_each_philosopher_must_eat] > 0\n");
	exit(1);
}

void	parsing(int argc, char **argv, t_table *table)
{
	table->philo_num = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->eat_times = ft_atoi(argv[5]);
	else
		table->eat_times = -1;
	if (table->philo_num < 2 || table->philo_num > 200
		|| table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60 || (table->eat_times < 1
			&& table->eat_times != -1) || table->eat_times == 0
		|| table->philo_num == 0 || table->time_to_die == 0
		|| table->time_to_eat == 0 || table->time_to_sleep == 0)
		usage();
	table->dead_count = 0;
}
