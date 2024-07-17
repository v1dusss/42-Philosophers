#include "philo.h"

bool	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (starved(philo) == true)
	{
		ft_printf(philo->id, DEAD, philo);
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	ft_printf(philo->id, L_FORK, philo);
	pthread_mutex_lock(philo->right_fork);
	if (starved(philo) == true)
	{
		ft_printf(philo->id, DEAD, philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	ft_printf(philo->id, R_FORK, philo);
	ft_printf(philo->id, EAT, philo);
	pthread_mutex_lock(&philo->last_eat_protection);
	philo->last_eat = get_timestap(philo);
	pthread_mutex_unlock(&philo->last_eat_protection);
	ft_usleep(get_time_to_eat(philo->table));
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
	ft_usleep(get_time_to_sleep(philo->table));
}

void	philo_think(t_philo *philo)
{
	ft_printf(philo->id, THINK, philo);
}

bool	starved(t_philo *philo)
{
	if ((get_timestap(philo) - get_last_eaten_dinner(philo->table,
				philo->id)) >= get_time_to_die(philo->table))
		return (true);
	return (false);
}
