/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:52:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/16 19:19:07 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <pthread.h>

void philo_philoing(t_philo_data *data)
{
	t_philo	*philo;
	t_mutex mutex_print;
	int		i;
	int		*dead;

	i = 0;
	philo = data->philo;
	pthread_mutex_init(&mutex_print, NULL);
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine, &data->philo[i]))
			ft_putstr("yooo\n");
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(philo[i].thread, (void **)&dead))
			ft_putstr("yooo2\n");
		if (dead && *dead)
		{
			return;
		}
		i++;
	}
	philo_philoing(data);	
}

int	main(int ac, char **av)
{
	t_philo_data	data;
	pthread_t oui;

	if (ac != 5)
		return (1);
	if (philo_init(av + 1, &data))
		return (1);
	pthread_mutex_init(&data.print_mutex, NULL);
	mutex_init(&data);
	philo_philoing(&data);
	mutex_destroy(&data);
	free(data.philo);
	return (0);
}
