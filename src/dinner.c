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
	t_table	*table;
	t_philo	*philo;

	table = (t_table *)arg;
	philo = table->philo;
	printf("philo %d is here\n", philo->id);
	if (table->philo_num % 2 == 0 && philo->id % 2 == 1)
	{
		ft_usleep(table->time_to_eat);
	}
	while (philo->dead == 0)
	{
		if (philo_think(philo) == 1)
		{
			free(philo);
			return (NULL);
		}
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

int	philo_think(t_philo *philo)
{
}

void	dinner_time(t_table *table)
{
	int	i;

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
