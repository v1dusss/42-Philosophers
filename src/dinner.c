/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:51:18 by vsivanat          #+#    #+#             */
/*   Updated: 2024/07/17 23:51:19 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		ft_usleep(get_time_to_eat(philo->table));
	while (get_end_dinner(philo->table) == false)
	{
		if (philo_eat(philo) == false)
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
	while (get_end_dinner(table) == false)
	{
		i = -1;
		table->finished_count = 0;
		while (++i < table->philo_num)
		{
			if (get_num_eaten_dinenrs(table, i + 1) >= table->eat_times)
				table->finished_count++;
			if (starved(&table->philo[i], i + 1) == true)
				ft_printf(i + 1, DEAD, &table->philo[i]);
		}
		if (table->eat_times > 0 && table->finished_count == table->philo_num)
		{
			pthread_mutex_lock(&table->end_dinner_protection);
			table->end_dinner = true;
			pthread_mutex_unlock(&table->end_dinner_protection);
			return (NULL);
		}
	}
	return (NULL);
}

bool	dinner_time(t_table *table)
{
	int	i;
	int	philo_num;

	i = -1;
	philo_num = table->philo_num;
	pthread_mutex_lock(&table->end_dinner_protection);
	table->end_dinner = false;
	pthread_mutex_unlock(&table->end_dinner_protection);
	get_start_time(table);
	while (++i < philo_num)
	{
		pthread_create(&table->philo[i].thread, NULL, philo_life,
			&table->philo[i]);
	}
	pthread_create(&table->waiter, NULL, waiter_life, table);
	i = -1;
	while (++i < philo_num)
	{
		pthread_join(table->philo[i].thread, NULL);
	}
	pthread_join(table->waiter, NULL);
	return (true);
}
