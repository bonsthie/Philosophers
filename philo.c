/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:52:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/26 17:12:45 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void set_to_dead(t_philo_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = true;
	pthread_mutex_unlock(&data->stop_mutex);
}


void	philo_philoing(t_philo_data *data)
{
	t_philo	*philo;
	int		*dead;
	int		i;

	i = 0;
	philo = data->philo;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine,
				&data->philo[i]))
		{
			print_status(EAT_MSG, data, philo[i].id, 0);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(philo[i].thread, (void **)&dead))
		{
			print_status(ERROR_JOIN , data, philo[i].id, 0);
			return ;
		}
		if (dead)
		{
			set_to_dead(data);
			printf(DIED_MSG, get_time() / 1000,	philo[i].id);
			return ;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo_data	data;

	if (ac != 5)
		return (1);
	if (philo_init(av + 1, &data))
		return (1);
	data.stop_mutex = (t_mutex){0};
	get_time();
	mutex_init(&data);
	philo_philoing(&data);
	mutex_destroy(&data);
	free(data.philo);
	return (0);
}
