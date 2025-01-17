/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:51:47 by vsivanat          #+#    #+#             */
/*   Updated: 2024/07/23 15:21:07 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;
typedef struct s_philo
{
	int					id;
	int					num_eaten_dinners;
	pthread_mutex_t		num_eaten_dinners_protection;
	int					last_meal;
	pthread_mutex_t		time_of_last_meal_protection;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	pthread_mutex_t		time_to_die_protection;
	pthread_mutex_t		time_to_eat_protection;
	pthread_mutex_t		time_to_sleep_protection;
	int					eat_times;
	int					end_dinner;
	pthread_mutex_t		end_dinner_protection;
	long long			start;
	pthread_mutex_t		start_protection;
	int					finished_count;
	pthread_mutex_t		*forks;
	pthread_t			waiter;
	pthread_mutex_t		printer;
	t_philo				*philo;
}						t_table;

# define L_FORK "\033[1;32mhas taken a fork\033[0m"
# define R_FORK "\033[1;32mhas taken a fork\033[0m"
# define EAT "\033[1;33mis eating\033[0m"
# define SLEEP "\033[1;34mis sleeping\033[0m"
# define THINK "\033[1;35mis thinking\033[0m"
# define DEAD "died"
# define ERROR_PHILO "\033[1;31mError: Failed to create philosophers\033[0m\n"

void					usage(void);
void					parsing(int argc, char **argv, t_table *table);
bool					dinner_time(t_table *table);
void					one_philo(t_table *table);

int						ft_atoi(const char *str);
int						ft_usleep(long long ms);
void					dinner_start_time(t_table *table);
long long				get_time(void);
int						timestamp(t_philo *philo);
void					ft_printf(int id, char *str, t_philo *philo);

int						time_to_eat_get(t_table *table);
int						time_to_sleep_get(t_table *table);
int						time_to_die_get(t_table *table);
bool					get_end_dinner(t_table *table);
int						get_num_eaten_dinenrs(t_table *table, int i);
int						time_of_last_meal_get(t_table *table, int i);
long long				dinner_start_time_get(t_table *table);

bool					philo_eat(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					philo_think(t_philo *philo);
bool					starved(t_philo *philo, int id);

#endif