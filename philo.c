/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:52:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/10 20:07:30 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdarg.h>


int new_thread(t_pthread *thread, ...)
{
	va_list ap;

	va_start(ap, thread);
	return(pthread_create(thread, NULL, &philo_routine, ap));
}

void philo_philoing(t_philo_data *data)
{
	t_philo	*philo;
	t_pthread_mutex mutex_print;
	int		i;

	i = 0;
	philo = data->philo;
	pthread_mutex_init(&mutex_print, NULL);
	while (i < data->philo_nb)
	{
		/* thread_arg = (t_thread_arg){&data->philo[i], data->time, &mutex_print}; */
		/* thread_arg.philo = &data->philo[i]; */
		if (new_thread(&data->philo[i].thread, &data->philo[i], data->time, &mutex_print))
			ft_putstr("yooo\n");
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(philo[i].thread, NULL))
			ft_putstr("yooo2\n");

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
	mutex_init(&data);
	philo_philoing(&data);
	mutex_destroy(&data);
	free(data.philo);
	return (0);
}
