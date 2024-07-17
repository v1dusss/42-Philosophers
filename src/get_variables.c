/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:51:41 by vsivanat          #+#    #+#             */
/*   Updated: 2024/07/17 23:51:43 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
