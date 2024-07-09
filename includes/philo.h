
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	int				dead_count;
	uint64_t		start_time;
}					t_table;

typedef struct s_philo
{
	int				id;
	int				eat_times;
	long long		last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_table			*table;
}					t_philo;

void				usage(void);
void				parsing(int argc, char **argv, t_table *table);

#endif