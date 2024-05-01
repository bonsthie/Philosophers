/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:43:36 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/01 16:22:44 by babonnet         ###   ########.fr       */
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

void	*philo_routine(void *args)
{
	t_philo			*philo;
	t_philo_data	*data;

	philo = args;
	data = philo->data;
	while (stop(philo->data) == false 
		&& (philo->eat_count > 0 || philo->eat_count == NO_EAT_COUNT))
	{
		if (take_forks(philo))
			return (PTHREAD_CANCELED);
		if (eat(philo, data, data->time))
			return (PTHREAD_CANCELED);
		if (sleep_action(philo, data, data->time))
			return (PTHREAD_CANCELED);

		print_status(THINK_MSG, data, get_time() / 1000, philo->id);
		if (philo->eat_count != NO_EAT_COUNT)
			philo->eat_count--;
	}
	return (PTHREAD_SUCCESS);
}
