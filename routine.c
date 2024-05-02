/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:43:36 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/02 13:58:53 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	take_fork(t_philo *philo, int fork_id)
{
	if (fork_id == 0)
		pthread_mutex_lock(&philo->fork_left);
	else
		pthread_mutex_lock(philo->fork_right);
	print_status(FORK_MSG, philo->data, get_time() / 1000, philo->id);
	return (0);
}

int	take_forks(t_philo *philo)
{
	take_fork(philo, philo->id % 2);
	take_fork(philo, (philo->id + 1) % 2);
	if (time_reamaning(philo) < 0)
	{
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	return (0);
}

int	eat(t_philo *philo, t_philo_data *data, t_time time)
{
	int	err;

	philo->last_ate = get_time();
	print_status(EAT_MSG, data, philo->last_ate / 1000, philo->id);
	err = philo_wait(philo, time.eat, time_reamaning(philo));
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (err);
}

int	sleep_action(t_philo *philo, t_philo_data *data, t_time time)
{
	print_status(SLEEP_MSG, data, get_time() / 1000, philo->id);
	return (philo_wait(philo, time.sleep, time_reamaning(philo)));
}

void *set_to_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count = -1;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	return (PTHREAD_CANCELED);
}

void eat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_count_mutex);
	if (philo->eat_count > 0)
		philo->eat_count--;
	pthread_mutex_unlock(&philo->eat_count_mutex);
}

void	*philo_routine(void *args)
{
	t_philo			*philo;
	t_philo_data	*data;

	philo = args;
	data = philo->data;
	while (philo_die(philo) > 0 || philo_die(philo) == NO_EAT_COUNT)
	{
		if (take_forks(philo))
			return (set_to_die(philo));
		if (eat(philo, data, data->time))
			return (set_to_die(philo));
		if (sleep_action(philo, data, data->time))
			return (set_to_die(philo));
		print_status(THINK_MSG, data, get_time() / 1000, philo->id);
		usleep(100);
		if (philo_die(philo) != NO_EAT_COUNT)
			eat_meal(philo);
	}
	while(philo_die(philo) == 0)
		usleep(WAIT_INTERVAL);
	return (PTHREAD_SUCCESS);
}
