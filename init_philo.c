/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:48:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/02 13:33:29 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/wchar.h>

int fill_number(char *str)
{
	char *endptr;
	long int i;

	if (!str)
		return (-1);
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
	while (*endptr && ft_isspace(*endptr))
		endptr++;
	if (*endptr)
		return (-1);
	return (i);
}

int create_philo(t_philo_data *data, int eat_count)
{
	t_philo	*philo;
	int i;

	philo = malloc(data->philo_nb * sizeof(t_philo));
	if (!philo)
		return (1);
	i = 0;
	while (i < data->philo_nb)
	{
		philo[i] = (t_philo){0};
		philo[i].fork_right = &philo[(i + 1) % data->philo_nb].fork_left;
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].eat_count = eat_count;
		philo[i].eat_count_mutex = (t_mutex){0};
		i++;
	}
	data->philo = philo;
	return (0);
}

int	philo_init(char *args[5], t_philo_data *data)
{
	int eat_count;

	data->philo_nb = fill_number(args[0]);
	data->time.die = fill_number(args[1]) * 1000;
	data->time.eat = fill_number(args[2]) * 1000;
	data->time.sleep = fill_number(args[3]) * 1000;
	if (args[4])
		eat_count = fill_number(args[4]);
	else
		eat_count = NO_EAT_COUNT;
	if (data->philo_nb <= 1 
		|| data->time.die < 0 
		|| data->time.eat < 0 
		|| data->time.sleep < 0
		|| eat_count == -1)
		return (1);
	data->stop = false;
	if (create_philo(data, eat_count))
		return (1);
	return (0);
}
