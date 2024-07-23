/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:51:27 by vsivanat          #+#    #+#             */
/*   Updated: 2024/07/23 15:21:07 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timestamp(t_philo *philo)
{
	return ((get_time() - dinner_start_time_get(philo->table)) / 1000);
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

long long	dinner_start_time_get(t_table *table)
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

int	time_of_last_meal_get(t_table *table, int id)
{
	int	last_meal;

	pthread_mutex_lock(&table->philo[id - 1].time_of_last_meal_protection);
	last_meal = table->philo[id - 1].last_meal;
	pthread_mutex_unlock(&table->philo[id - 1].time_of_last_meal_protection);
	return (last_meal);
}
