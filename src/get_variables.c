#include "philo.h"

int	get_time_to_eat(t_table *table)
{
	int	time_to_eat;

	pthread_mutex_lock(&table->time_to_eat_protection);
	time_to_eat = table->time_to_eat;
	pthread_mutex_unlock(&table->time_to_eat_protection);
	return (time_to_eat);
}
int	get_time_to_sleep(t_table *table)
{
	int	time_to_sleep;

	pthread_mutex_lock(&table->time_to_sleep_protection);
	time_to_sleep = table->time_to_sleep;
	pthread_mutex_unlock(&table->time_to_sleep_protection);
	return (time_to_sleep);
}

int	get_time_to_die(t_table *table)
{
	int	time_to_die;

	pthread_mutex_lock(&table->time_to_die_protection);
	time_to_die = table->time_to_die;
	pthread_mutex_unlock(&table->time_to_die_protection);
	return (time_to_die);
}

bool	get_end_dinner(t_table *table)
{
	bool	end_dinner;

	pthread_mutex_lock(&table->end_dinner_protection);
	end_dinner = table->end_dinner;
	pthread_mutex_unlock(&table->end_dinner_protection);
	return (end_dinner);
}

int	get_num_eaten_dinenrs(t_table *table, int i)
{
	int	num_eaten_dinners;

	pthread_mutex_lock(&table->philo[i - 1].num_eaten_dinners_protection);
	num_eaten_dinners = table->philo[i - 1].num_eaten_dinners;
	pthread_mutex_unlock(&table->philo[i - 1].num_eaten_dinners_protection);
	return (num_eaten_dinners);
}

int	get_last_eaten_dinner(t_table *table, int i)
{
	int	last_eat;

	pthread_mutex_lock(&table->philo[i - 1].last_eat_protection);
	last_eat = table->philo[i - 1].last_eat;
	pthread_mutex_unlock(&table->philo[i - 1].last_eat_protection);
	return (last_eat);
}

long long	get_start(t_table *table)
{
	long long	start;

	pthread_mutex_lock(&table->start_protection);
	start = table->start;
	pthread_mutex_unlock(&table->start_protection);
	return (start);
}

int	get_timestap(t_philo *philo)
{
	return ((get_time() - get_start(philo->table)) / 1000);
}

long long	get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error: gettimeofday\n");
		return (-1);
	}
	return (time.tv_sec * 1000000 + time.tv_usec);
}