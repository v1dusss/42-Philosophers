#include "philo.h"

void	ft_free(t_table *table)
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
	pthread_mutex_init(&table->printer, NULL);
	pthread_mutex_init(&table->time_to_die_protection, NULL);
	pthread_mutex_init(&table->time_to_eat_protection, NULL);
	pthread_mutex_init(&table->time_to_sleep_protection, NULL);
	pthread_mutex_init(&table->end_dinner_protection, NULL);
	pthread_mutex_init(&table->start_protection, NULL);
	while (++i < table->philo_num)
		pthread_mutex_init(&table->forks[i], NULL);
	i = -1;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->philo_num + 1);
	if (!table->philo)
		return (ft_free(table), false);
	while (++i < table->philo_num)
	{
		table->philo[i].id = i + 1;
		table->philo[i].num_eaten_dinners = 0;
		table->philo[i].last_eat = 0;
		(table->philo[i].left_fork = &table->forks[i]);
		(table->philo[i].right_fork = &table->forks[(i + 1)
			% table->philo_num]);
		pthread_mutex_init(&table->philo[i].num_eaten_dinners_protection, NULL);
		pthread_mutex_init(&table->philo[i].last_eat_protection, NULL);
		table->philo[i].table = table;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		usage();
	parsing(argc, argv, &table);
	if (!create_philo(&table))
		return (printf(ERROR_PHILO), 1);
	if (!dinner_time(&table))
		return (1);
	ft_free(&table);
	return (0);
}
