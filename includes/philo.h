
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct data_s
{
	int				num;
	pthread_mutex_t	mutex;
	data_t			*next;
}					data_t;

#endif