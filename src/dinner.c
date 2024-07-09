#include "philo.h"

void	*waiter_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("waiter is here\n");
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("philo %d is here\n", philo->id);
	return (NULL);
}

void	dinner_time(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->philo_num)
	{
		pthread_create(&table->philo[i].thread, NULL, philo_life,
			&table->philo[i]);
	}
	pthread_create(&table->waiter, NULL, waiter_life, table);
	i = -1;
	while (++i < table->philo_num)
	{
		pthread_join(table->philo[i].thread, NULL);
	}
}