/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:48:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/08 23:47:51 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int fill_number(char *str)
{
	char *endptr;
	long int i;

	while (*str && ft_isspace(*str))
		str++;
	if (!*str)
		return (-1);
	i = ft_strtol(str, &endptr, 10);
	if ((*endptr && !ft_isdigit(*endptr) && !ft_isspace(*endptr))
		|| i < 0 || i > MAX_INT)
		return (-1);
	if (endptr - str > 11)
		return (-1);
	return (i);
}

int	philo_init(char *args[4], t_philo_data *data)
{
	data->philo_nb = fill_number(args[0]);
	data->time_die = fill_number(args[1]);
	data->time_eat = fill_number(args[2]);
	data->time_sleep = fill_number(args[3]);
	if (data->philo_nb < 0 
		|| data->time_die < 0 
		|| data->time_eat < 0 
		|| data->time_sleep < 0)
		return (1);
	data->philo = malloc(data->philo_nb * sizeof(t_philo));
	if (!data->philo)
		return (1);
	return (0);
}
