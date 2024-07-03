/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:53:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/19 15:55:09 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec * MICROSECOND + tv.tv_usec) / 1000);
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
		if (!stop(&philo->data->stop, get_stop_value))
			return (0);
		if (time_to_die <= 0)
			return (1);
		usleep(WAIT_INTERVAL * 1000);
		time_to_sleep -= WAIT_INTERVAL;
		time_to_die -= WAIT_INTERVAL;
	}
	if (time_to_sleep > time_to_die)
	{
		usleep(time_to_die * 1000);
		return (1);
	}
	if (time_to_sleep > 0)
		usleep(time_to_sleep * 1000);
	return (0);
}

long long	time_reamaning(t_philo *philo)
{
	return (philo->data->time.die - (get_time() - philo->last_ate));
}
