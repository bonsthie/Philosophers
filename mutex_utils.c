/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/16 19:21:15 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_status(char *str, t_philo_data *data, long long int time,
		int philo_id)
{
	static t_mutex	print_mutex = {0};

	if (stop(&data->stop, get_stop_value) == 0)
		return ;
	pthread_mutex_lock(&print_mutex);
	if (stop(&data->stop, get_stop_value))
		printf(str, time, philo_id);
	pthread_mutex_unlock(&print_mutex);
}

void	*philo_die(t_philo *philo)
{
	static bool	dead = false;

	stop(&philo->data->stop, set_to_stop);
	if (!dead++)
		printf(DIED_MSG, get_time() / 1000, philo->id);
	return (PTHREAD_CANCELED);
}
