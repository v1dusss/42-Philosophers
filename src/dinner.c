#include "philo.h"

bool	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if ((get_timestap(*philo) - philo->last_eat) >= philo->table->time_to_die)
	{
		ft_printf(philo->id, DEAD, philo);
		return (false);
	}
	ft_printf(philo->id, FORK, philo);
	pthread_mutex_lock(philo->right_fork);
	if ((get_timestap(*philo) - philo->last_eat) > philo->table->time_to_die)
	{
		ft_printf(philo->id, DEAD, philo);
		return (false);
	}
	ft_printf(philo->id, FORK, philo);
	ft_printf(philo->id, EAT, philo);
	philo->last_eat = get_timestap(*philo);
	philo->eat_times++;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

void	philo_sleep(t_philo *philo)
{
	ft_printf(philo->id, SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	ft_printf(philo->id, THINK, philo);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		ft_usleep(philo->table->time_to_eat);
	while (!philo->table->end_dinner)
	{
		if (!philo_eat(philo))
			return (NULL);
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
	while (!table->end_dinner)
	{
		i = -1;
		table->finished_count = 0;
		while (++i < table->philo_num)
		{
			if (table->philo[i].eat_times >= table->eat_times)
				table->finished_count++;
		}
		if (table->eat_times > 0 && table->finished_count == table->philo_num)
		{
			table->end_dinner = 1;
			break ;
		}
	}
	return (NULL);
}

bool	dinner_time(t_table *table)
{
	int	i;

	i = -1;
	get_start_time(table);
	table->end_dinner = 0;
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
	pthread_join(table->waiter, NULL);
	return (true);
}
