/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:48:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/16 20:27:00 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int is_invalid_char(char c)
{
    return ((c && !ft_isdigit(c) && !ft_isspace(c)));
}

long	fill_number(char *str)
{
	char		*endptr;
	long	i;

	if (!str)
		return (-1);
	while (*str && ft_isspace(*str))
		str++;
	if (!*str)
		return (-1);
	i = ft_strtoll(str, &endptr, 10);
	if (is_invalid_char(*endptr) || i <= 0 || i > MAX_INT)
		return (-1);
	if (endptr - str > 11)
		return (-1);
	while (*endptr && ft_isspace(*endptr))
		endptr++;
	if (*endptr)
		return (-1);
	return (i);
}

int	create_philo(t_philo_data *data, int eat_count)
{
	t_philo	*philo;
	int		i;

	philo = malloc(data->philo_nb * sizeof(t_philo));
	if (!philo)
		return (1);
	data->philo = philo;
	i = 0;
	while (i < data->philo_nb)
	{
		philo[i] = (t_philo){0};
		philo[i].fork_left = (t_mutex){0};
		philo[i].fork_right = &philo[(i + 1) % data->philo_nb].fork_left;
		philo[i].data = data;
		philo[i].eat_count = eat_count;
		philo[i].id = i + 1;
		i++;
	}
	return (0);
}

int	philo_init(char *args[4], t_philo_data *data)
{
	int	eat_count;

	data->philo_nb = fill_number(args[0]);
	data->time.die = fill_number(args[1]);
	data->time.eat = fill_number(args[2]);
	data->time.sleep = fill_number(args[3]);
	if (args[4])
		eat_count = fill_number(args[4]);
	else
		eat_count = NO_EAT_COUNT;
	if (data->philo_nb <= 0
		|| data->time.die < 0
		|| data->time.eat < 0
		|| data->time.sleep < 0
		|| eat_count == -1)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	data->stop = data->philo_nb;
	if (create_philo(data, eat_count))
		return (1);
	return (0);
}
