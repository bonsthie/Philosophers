/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:43:36 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/10 19:53:24 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdarg.h>
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

void *__philo_routine(t_philo *philo, t_time time, t_pthread_mutex *print_mutex)
{
	print_status("%d philo %d eat\n", print_mutex, 0, philo->id);
	/* take_fork(philo, philo->id % 2); */
	/* take_fork(philo, (philo->id + 1) % 2); */
	/* philo->status = EAT; */
	/* sleep(1); */
	/* pthread_mutex_unlock(&philo->fork_left); */
	/* pthread_mutex_unlock(philo->fork_right); */
	//print_status("%d philo %d think\n", print_mutex, 0, philo->id);
	(void)time;
	(void)print_mutex;
	ft_putstr("test 4\n");
	return (NULL);
}

void *philo_routine(void *args)
{
	va_list *ap;

	ap = args;
	return (__philo_routine(va_arg(*ap, t_philo *),
						 va_arg(*ap, t_time),
						 va_arg(*ap, t_pthread_mutex *)));
}
