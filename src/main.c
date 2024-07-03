#include "philo.h"

void	print_current_time(void)
{
	struct timeval	tv_start;
	struct timeval	tv;

	if (gettimeofday(&tv_start, NULL))
		exit(1);
	usleep(1000000);
	if (gettimeofday(&tv, NULL))
		exit(1);
	printf("duration in Milliseconds: %ld\n", (tv.tv_sec - tv_start.tv_sec)
		* 1000 + (tv.tv_usec - tv_start.tv_usec) / 1000);
}

void	*print_hello(void *arg)
{
	int	i;

	i = 0;
	(void)arg;
	while (i < 10)
	{
		printf("Hello\n");
		i++;
	}
	return (NULL);
}

void	*print_world(void *arg)
{
	int	i;

	i = 0;
	(void)arg;
	while (i < 10)
	{
		printf("\tWorld\n");
		i++;
	}
	return (NULL);
}

void	*hallo(void *arg)
{
	int	*num;
	int	i;

	num = (int *)arg;
	i = 0;
	while (i < 10000)
	{
		(*num)++;
		i++;
	}
	return (NULL);
}

data_t	*create_data(void)
{
	data_t	*data;

	data = malloc(sizeof(data_t));
	if (!data)
		exit(1);
	data->num = 0;
	if (pthread_mutex_init(&data->mutex, NULL))
		exit(1);
	return (data);
}

void	*hallo2(void *arg)
{
	data_t	*data;
	int		i;

	data = (data_t *)arg;
	i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&data->mutex);
		(data->num)++;
		pthread_mutex_unlock(&data->mutex);
		i++;
	}
	return (NULL);
}

int	main(void)
{
	data_t *data;
	pthread_t thread1;
	pthread_t thread2;

	data = create_data();

	pthread_create(&thread1, NULL, hallo2, data);
	pthread_create(&thread2, NULL, hallo2, data);
	usleep(10);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("num: %d\n", data->num);
	pthread_mutex_destroy(&data->mutex);
	free(data);
	return (0);
}