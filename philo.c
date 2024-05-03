/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:52:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/03 18:20:37 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void	monitor(t_philo *philo)
{
	(void)philo;
}

static void	start_philo(t_philo *philo, int philo_nb)
{
	t_philo	*endptr;

	endptr = philo + philo_nb;
	while (philo < endptr)
	{
		pthread_create(&philo->thread, NULL, philo_routine, philo);
		philo++;
	}
}

static void	join_philo(t_philo *philo, int philo_nb)
{
	t_philo	*endptr;

	endptr = philo + philo_nb;
	while (philo < endptr)
	{
		pthread_join(philo->thread, NULL);
		philo++;
	}
}

static void	philo_philoing(t_philo_data *data)
{
	start_philo(data->philo, data->philo_nb);
	monitor(data->philo);
	join_philo(data->philo, data->philo_nb);
}

int	main(int ac, char **av)
{
	t_philo_data	data;

	if (ac < 5 || ac > 6)
		return (1);
	if (philo_init(av + 1, &data))
		return (1);
	if (data.philo_nb == 1)
	{
		printf(DIED_MSG, (long long)0, 1);
		return (0);
	}
	get_time();
	mutex_init(&data);
	philo_philoing(&data);
	mutex_destroy(&data);
	free(data.philo);
	return (0);
}
