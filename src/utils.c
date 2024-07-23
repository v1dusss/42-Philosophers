/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:51:37 by vsivanat          #+#    #+#             */
/*   Updated: 2024/07/23 15:13:22 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	dinner_start_time(t_table *table)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit(1);
	table->start = tv.tv_sec * 1000000 + tv.tv_usec;
}

void	ft_printf(int id, char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->printer);
	if (get_end_dinner(philo->table) == true)
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
	printf("%d %d %s\n", timestamp(philo), id, str);
	pthread_mutex_unlock(&philo->table->printer);
}

void	one_philo(t_table *table)
{
	printf("0 1 "L_FORK"\n");
	ft_usleep(table->time_to_die);
	printf("%d 1 "DEAD"\n", table->time_to_die);
	exit(0);
}
