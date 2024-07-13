#include "philo.h"

void	print_parsing(t_table *table)
{
	printf("philo_num: %d\n", table->philo_num);
	printf("time_to_die: %d\n", table->time_to_die);
	printf("time_to_eat: %d\n", table->time_to_eat);
	printf("time_to_sleep: %d\n", table->time_to_sleep);
	if (table->eat_times != -1)
		printf("eat_times: %d\n", table->eat_times);
	printf("\033[1;32mParsing is done! \033[0m\n");
}

void	destory_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->forks);
	if (table->philo)
		free(table->philo);
}

bool	create_philo(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (false);
	while (++i < table->philo_num)
		pthread_mutex_init(&table->forks[i], NULL);
	i = -1;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->philo_num + 1);
	while (++i < table->philo_num)
	{
		table->philo[i].id = i + 1;
		table->philo[i].eat_times = 0;
		table->philo[i].last_eat = 0;
		table->philo[i].dead = 0;
		table->philo[i].finished = 0;
		(table->philo[i].left_fork = &table->forks[i]);
		(table->philo[i].right_fork = &table->forks[(i + 1)
			% table->philo_num]);
		table->philo[i].table = table;
		// printf("philo struct %d created\n", table->philo[i].id);
	}
	i = -1;
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		usage();
	parsing(argc, argv, &table);
	// print_parsing(&table);
	if (!create_philo(&table))
		return (printf(ERROR_PHILO), destory_forks(&table), 1);
	dinner_time(&table);
	return (0);
}
