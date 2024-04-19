/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:52:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/18 13:21:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

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
			data->stop = true;
			printf(DIED_MSG, 0,	philo[i].id);
			return ;
		}
		i++;
	}
	philo_philoing(data);
}

int	main(int ac, char **av)
{
	t_philo_data	data;

	if (ac != 5)
		return (1);
	if (philo_init(av + 1, &data))
		return (1);
	data.print_mutex = (t_mutex){0};
	mutex_init(&data);
	philo_philoing(&data);
	mutex_destroy(&data);
	free(data.philo);
	return (0);
}
