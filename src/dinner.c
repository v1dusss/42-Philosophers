#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("%dms %d took left fork\n", get_timestap(*philo), philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%dms %d took right fork\n", get_timestap(*philo), philo->id);
	printf("%dms %d is eating\n", get_timestap(*philo), philo->id);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*waiter_life(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	printf("waiter is searving for %d philos\n", table->philo_num);
	return (NULL);
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
	// while (philo->dead == 0)
	// {
	philo_eat(philo);
	// philo_sleep(philo);
	// 	philo_think(philo);
	// }
	return (NULL);
}

// int	philo_think(t_philo *philo)
// {
// }

void	dinner_time(t_table *table)
{
	int	i;

	i = -1;
	get_start_time(table);
	printf("dinner time at %lld\n", table->start);
	printf("Starting dinner for %d philos\n", table->philo_num);
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
