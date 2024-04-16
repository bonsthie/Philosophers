/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:43:36 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/16 19:15:41 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

size_t ft_strlen(const char *str)
{
	const char *endptr;

	endptr = str;
	while(*endptr)
		endptr++;
	return (endptr - str);
}

int ft_putstr(const char *str)
{
	return (write(1, str, ft_strlen(str)));
}

int take_fork(t_philo *philo, int fork_id)
{
	if (fork_id == 0)
	{
		if (pthread_mutex_lock(&philo->fork_left))
			return (1);
		return (0);
	}
	if (pthread_mutex_lock(philo->fork_right))
		return (1);
	return (0);
}

void *__philo_routine(t_philo *philo, t_time time, t_mutex *print_mutex)
{
	int *error = malloc(sizeof(int));

	*error = 1;
	take_fork(philo, philo->id % 2);
	take_fork(philo, (philo->id + 1) % 2);
	print_status("%d philo %d eat\n", print_mutex, 0, philo->id);
	philo->status = EAT;
	sleep(1);
	if (philo->id == 4)
	{
		write(2, "ah\n", 3);
		return ((void *)error);
	}
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	print_status("%d philo %d think\n", print_mutex, 0, philo->id);
	(void)time;
	(void)print_mutex;
	return (NULL);
}

void *philo_routine(void *args)
{
	t_philo *philo;

	philo = args;
	return (__philo_routine(philo,
							philo->data->time,
						 	&philo->data->print_mutex));
}
