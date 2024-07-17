/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:51:27 by vsivanat          #+#    #+#             */
/*   Updated: 2024/07/17 23:51:31 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_timestap(t_philo *philo)
{
	return ((get_time() - get_start(philo->table)) / 1000);
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

long long	get_start(t_table *table)
{
	long long	start;

	pthread_mutex_lock(&table->start_protection);
	start = table->start;
	pthread_mutex_unlock(&table->start_protection);
	return (start);
}

int	get_num_eaten_dinenrs(t_table *table, int id)
{
	int	num_eaten_dinners;

	pthread_mutex_lock(&table->philo[id - 1].num_eaten_dinners_protection);
	num_eaten_dinners = table->philo[id - 1].num_eaten_dinners;
	pthread_mutex_unlock(&table->philo[id - 1].num_eaten_dinners_protection);
	return (num_eaten_dinners);
}

int	get_last_eaten_dinner(t_table *table, int id)
{
	int	last_eat;

	pthread_mutex_lock(&table->philo[id - 1].last_eat_protection);
	last_eat = table->philo[id - 1].last_eat;
	pthread_mutex_unlock(&table->philo[id - 1].last_eat_protection);
	return (last_eat);
}
