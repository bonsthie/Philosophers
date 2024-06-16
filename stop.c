/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:20:30 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/16 19:18:25 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_to_stop(int *stop)
{
	*stop = 0;
	return (0);
}

int	get_stop_value(int *stop)
{
	return (*stop);
}

int	decrement_stop(int *stop)
{
	if (*stop)
		(*stop)--;
	return (*stop);
}

int	stop(int *stop, int f(int *))
{
	static t_mutex	mutex = {0};
	int				stop_result;

	pthread_mutex_lock(&mutex);
	stop_result = f(stop);
	pthread_mutex_unlock(&mutex);
	return (stop_result);
}
