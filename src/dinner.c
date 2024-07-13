#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if ((get_timestap(*philo) - philo->last_eat) >= philo->table->time_to_die)
	{
		printf("%d %d died\n", get_timestap(*philo), philo->id);
		philo->dead = 1;
		philo->table->dead_count = 1;
		exit(1);
	}
	printf("%d %d has taken a fork\n", get_timestap(*philo), philo->id);
	pthread_mutex_lock(philo->right_fork);
	if ((get_timestap(*philo) - philo->last_eat) > philo->table->time_to_die)
	{
		printf("%d %d died\n", get_timestap(*philo), philo->id);
		philo->dead = 1;
		philo->table->dead_count = 1;
		exit(1);
	}
	printf("%d %d has taken a fork\n", get_timestap(*philo), philo->id);
	printf("%d %d is eating\n", get_timestap(*philo), philo->id);
	philo->last_eat = get_timestap(*philo);
	philo->eat_times++;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	printf("%d %d is sleeping\n", get_timestap(*philo), philo->id);
	ft_usleep(philo->table->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	printf("%d %d is thinking\n", get_timestap(*philo), philo->id);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// printf("philo %d/%d is here\n", philo->id, philo->table->philo_num);
	if (philo->id % 2 == 1)
	{
		ft_usleep(philo->table->time_to_eat);
		// printf("*philo %d is waiting\n", philo->id);
	}
	while (philo->eat_times != philo->table->eat_times)
	{
		philo_eat(philo);
		if (philo->eat_times == philo->table->eat_times)
		{
			if (philo->table->philo_num % 2
				&& philo->table->finished_eat == philo->table->philo_num)
				return (NULL);
			if (!philo->table->philo_num % 2
				&& philo->table->finished_eat >= philo->table->philo_num / 2)
				return (NULL);
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*waiter_life(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (table->finished_eat != table->philo_num)
	{
		if (table->dead_count)
			return (NULL);
		i = -1;
		while (++i < table->philo_num)
		{
			if (table->philo[i].eat_times == table->eat_times
				&& table->philo[i].finished == 0)
			{
				table->finished_eat++;
				table->philo[i].finished = 1;
			}
		}
	}
	return (NULL);
}

void	dinner_time(t_table *table)
{
	int	i;

	i = -1;
	get_start_time(table);
	// printf("dinner time at %lld\n", table->start);
	// printf("Starting dinner for %d philos\n", table->philo_num);
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
