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

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error: gettimeofday\n");
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(long long ms)
{
	long long	start;

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
