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

int	get_timestap(t_philo philo)
{
	return ((get_time() - philo.table->start) / 1000);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error: gettimeofday\n");
		return (-1);
	}
	return (time.tv_sec * 1000000 + time.tv_usec);
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
	if (philo->table->end_dinner)
	{
		pthread_mutex_unlock(&philo->table->printer);
		return ;
	}
	if (str[0] == 'd')
	{
		printf("Test\n");
		philo->table->end_dinner = 1;
	}
	printf("%d %d %d %s\n", get_timestap(*philo), id, philo->table->end_dinner,
		str);
	pthread_mutex_unlock(&philo->table->printer);
}