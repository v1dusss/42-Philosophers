
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
	int					eat_times;
	int					last_eat;
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
	int					eat_times;
	int					end_dinner;
	long long			start;
	int					finished_count;
	pthread_mutex_t		*forks;
	pthread_t			waiter;
	pthread_mutex_t		printer;
	t_philo				*philo;
}						t_table;

# define FORK "\033[1;32mhas taken a fork\033[0m"
# define EAT "\033[1;33mis eating\033[0m"
# define SLEEP "\033[1;34mis sleeping\033[0m"
# define THINK "\033[1;35mis thinking\033[0m"
# define DEAD "died"
# define ERROR_PHILO "\033[1;31mError: Failed to create philosophers\033[0m\n"

void					usage(void);
void					parsing(int argc, char **argv, t_table *table);
bool					dinner_time(t_table *table);

int						ft_atoi(const char *str);
int						ft_usleep(long long ms);
void					get_start_time(t_table *table);
long long				get_time(void);
int						get_timestap(t_philo philo);
void					ft_printf(int id, char *str, t_philo *philo);

#endif