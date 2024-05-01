/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/01 17:32:18 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy(t_philo_data *data)
{
	int	i;

	i = 0;
	//destroy all data mutex
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->philo[i].fork_left);
		pthread_mutex_destroy(&data->philo[i].eat_count_mutex);
		i++;
	}
}

void	mutex_init(t_philo_data *data)
{
	int	i;

	i = 0;
	data->stop_mutex = (t_mutex){0};
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->philo[i].fork_left, NULL);
		i++;
	}
}

void	print_status(char *str, t_philo_data *data, long long int time,
		int philo_id)
{
	static t_mutex print_mutex = {0};

	if (stop(data) == true)
		return ;
	pthread_mutex_lock(&print_mutex);
	if (stop(data) == false)
		printf(str, time, philo_id);
	pthread_mutex_unlock(&print_mutex);
}

bool stop(t_philo_data *data)
{
	bool stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}
