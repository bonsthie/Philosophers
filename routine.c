/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:43:36 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/19 16:22:52 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int take_fork(t_philo *philo, int fork_id)
{
	if (fork_id == 0)
	{
		if (pthread_mutex_lock(&philo->fork_left))
			return (1);
	}
	else
	{
		if (pthread_mutex_lock(philo->fork_right))
			return (1);
	}
	print_status(FORK_MSG, philo->data, 0, philo->id);
	return (0);
}

int is_dead(t_philo *philo)
{
	(void)philo;
	int i  = strlen("tests");
	return (i);
}

static void *__philo_routine(t_philo *philo, t_philo_data *data)
{
	int err;

	take_fork(philo, philo->id % 2);
	// check if died
	take_fork(philo, (philo->id + 1) % 2);
	// check if died
	print_status(EAT_MSG, data, 0, philo->id);
	err = philo_wait(philo, 1, 2);
	if (!err)
	{
		print_status(SLEEP_MSG, data, 0, philo->id);
		err = philo_wait(philo, 1, 0);
	}
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	if (err)
		return (PTHREAD_CANCELED);
	print_status(THINK_MSG, data, 0, philo->id);
	return (PTHREAD_SUCCESS);
}

void *philo_routine(void *args)
{
	t_philo *philo;

	philo = args;
	return (__philo_routine(philo,
							philo->data));
}
