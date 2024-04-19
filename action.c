/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:26:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/18 14:56:49 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_wait(t_philo *philo, int time_to_sleep, int time_to_die)
{
	if (philo->data->stop == true)
		return (0);
	while (time_to_sleep)
	{
		if(!time_to_die)
			return (1);
		usleep(WAIT_INTERVAL);
		time_to_sleep--;
		time_to_die--;
	}
	(void)philo;
	return (0);
}

//think
//see if dead
//take both fork
//wait of eat and verify if he die
//same with sleep
//goto start
