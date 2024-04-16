/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:48:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/16 18:18:10 by babonnet         ###   ########.fr       */
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
	while (*endptr && ft_isspace(*endptr))
		endptr++;
	if (*endptr)
		return (-1);
	return (i);
}

int create_philo(t_philo_data *data)
{
	t_philo	*philo;
	int i;

	printf("size %d\n", data->philo_nb);
	philo = malloc(data->philo_nb * sizeof(t_philo));
	if (!philo)
		return (1);
	i = 0;
	while (i < data->philo_nb)
	{
		philo[i].fork_right = &philo[(i + 1) % data->philo_nb].fork_left;
		philo[i].status = NOTHING;
		philo[i].data = data;
		philo[i].id = i + 1;
		i++;
	}
	data->philo = philo;
	return (0);
}

int	philo_init(char *args[4], t_philo_data *data)
{

	data->philo_nb = fill_number(args[0]);
	data->time.die = fill_number(args[1]);
	data->time.eat = fill_number(args[2]);
	data->time.sleep = fill_number(args[3]);
	if (data->philo_nb < 0 
		|| data->time.die < 0 
		|| data->time.eat < 0 
		|| data->time.sleep < 0)
		return (1);
	if (create_philo(data))
		return (1);
	return (0);
}
