#include "philo.h"
#include <sys/time.h>

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * MICROSECOND + tv.tv_usec);
}

long long	get_time(void)
{
	static long long	start;
	long long			time;

	time = get_current_time();
	if (!start)
		start = time;
	return ((get_current_time() - start));
}

int	philo_wait(t_philo *philo, long long time_to_sleep, long long time_to_die)
{
	while (time_to_sleep >= WAIT_INTERVAL)
	{
		if (stop(philo->data) == true)
			return (0);
		if (time_to_die <= 0)
			return (1);
		usleep(WAIT_INTERVAL);
		time_to_sleep -= WAIT_INTERVAL;
		time_to_die -= WAIT_INTERVAL;
	}
//	if (time_to_sleep > time_to_die)
//	{
//		usleep(time_to_die);
//		return (1);
//	}
	if (time_to_sleep > 0)
		usleep(time_to_sleep);
	return (0);
}

long long	time_reamaning(t_philo *philo)
{
	return (philo->data->time.die - (get_time() - philo->last_ate));
}

void philo_finish(t_philo_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop > 0)
		data->stop--;
	pthread_mutex_unlock(&data->stop_mutex);
}

void set_to_stop(t_philo_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 0;
	pthread_mutex_unlock(&data->stop_mutex);
}
