/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/25 18:55:21 by babonnet         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->philo[i].fork_left, NULL);
		i++;
	}
}

void	print_status(char *str, t_philo_data *data, long long int time,
		int philo_id)
{
	if (is_dead(data) == true)
		return ;
	pthread_mutex_lock(&data->print_mutex);
	if (is_dead(data) == false)
		printf(str, time, philo_id);
	pthread_mutex_unlock(&data->print_mutex);
}

bool is_dead(t_philo_data *data)
{
	bool is_dead;

	pthread_mutex_lock(&data->stop_mutex);
	is_dead = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (is_dead);
}
