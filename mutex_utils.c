/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/03 19:04:13 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->philo[i].fork_left);
		i++;
	}
}

void	mutex_init(t_philo_data *data)
{
	data->stop_mutex = (t_mutex){0};
}

void	print_status(char *str, t_philo_data *data, long long int time,
		int philo_id)
{
	static t_mutex	print_mutex = {0};

	if (stop(data) == 0)
		return ;
	pthread_mutex_lock(&print_mutex);
	if (stop(data))
		printf(str, time, philo_id);
	pthread_mutex_unlock(&print_mutex);
}

int	stop(t_philo_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	*philo_die(t_philo *philo)
{
	static bool	dead = false;

	set_to_stop(philo->data);
	if (!dead++)
		printf(DIED_MSG, get_time() / 1000, philo->id);
	return (PTHREAD_CANCELED);
}
