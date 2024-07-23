/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:51:33 by vsivanat          #+#    #+#             */
/*   Updated: 2024/07/23 15:19:52 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death(t_philo *philo, bool left_fork, bool right_fork)
{
	if (right_fork == true)
		pthread_mutex_unlock(philo->right_fork);
	if (left_fork == true)
		pthread_mutex_unlock(philo->left_fork);
	ft_printf(philo->id, DEAD, philo);
}

bool	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (starved(philo, philo->id) == true)
	{
		death(philo, true, false);
		return (false);
	}
	ft_printf(philo->id, L_FORK, philo);
	pthread_mutex_lock(philo->right_fork);
	if (starved(philo, philo->id) == true)
	{
		death(philo, true, true);
		return (false);
	}
	ft_printf(philo->id, R_FORK, philo);
	ft_printf(philo->id, EAT, philo);
	pthread_mutex_lock(&philo->time_of_last_meal_protection);
	philo->last_meal = timestamp(philo);
	pthread_mutex_unlock(&philo->time_of_last_meal_protection);
	ft_usleep(time_to_eat_get(philo->table));
	pthread_mutex_lock(&philo->num_eaten_dinners_protection);
	philo->num_eaten_dinners++;
	pthread_mutex_unlock(&philo->num_eaten_dinners_protection);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

void	philo_sleep(t_philo *philo)
{
	ft_printf(philo->id, SLEEP, philo);
	ft_usleep(time_to_sleep_get(philo->table));
}

void	philo_think(t_philo *philo)
{
	ft_printf(philo->id, THINK, philo);
}

bool	starved(t_philo *philo, int id)
{
	if ((timestamp(philo) - time_of_last_meal_get(philo->table,
				id)) >= time_to_die_get(philo->table))
		return (true);
	return (false);
}
