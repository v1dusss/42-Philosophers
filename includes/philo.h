
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				eat_times;
	long long		last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
}					t_philo;
typedef struct s_table
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	int				dead_count;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}					t_table;

# define ERROR_PHILO "\033[1;31mError: Failed to create philosophers\033[0m\n"

void				usage(void);
void				parsing(int argc, char **argv, t_table *table);

#endif