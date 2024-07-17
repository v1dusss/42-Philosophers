#include "philo.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		a;
	int		k;

	i = 0;
	a = 1;
	k = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		i++;
	if (str[i] == '-')
		a = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		k = k * 10 + (str[i++] - '0');
		if (str[i] < '0' || str[i] > '9')
			return (k * a);
	}
	return (0);
}

int	ft_usleep(long long ms)
{
	long long	start;

	ms = ms * 1000;
	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
	return (0);
}

void	get_start_time(t_table *table)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit(1);
	table->start = tv.tv_sec * 1000000 + tv.tv_usec;
}

void	ft_printf(int id, char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->printer);
	if (get_end_dinner(philo->table))
	{
		pthread_mutex_unlock(&philo->table->printer);
		return ;
	}
	if (str[0] == 'd')
	{
		pthread_mutex_lock(&philo->table->end_dinner_protection);
		philo->table->end_dinner = true;
		pthread_mutex_unlock(&philo->table->end_dinner_protection);
	}
	printf("%d %d %s\n", get_timestap(philo), id, str);
	pthread_mutex_unlock(&philo->table->printer);
}
