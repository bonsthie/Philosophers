/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:20:25 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/08 23:04:14 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

#define MAX_INT 0x7FFFFFFF

typedef pthread_mutex_t		t_pthread_mutex;

typedef unsigned long int	t_pthread;

typedef enum e_status
{
	EAT,
	THINK,
	SLEEP,
}							t_status;

typedef struct s_philo
{
	t_pthread				tag;
	t_pthread_mutex			mutex;
	t_status				status;
	long long				time;
	long long				last_ate;
}							t_philo;

typedef struct s_philo_data
{
	t_philo					*philo;
	int						philo_nb;
	int						time_eat;
	int						time_sleep;
	int						time_die;
}							t_philo_data;

// utils function
int	ft_isdigit(int c);
int	ft_isspace(int c);
int	ft_toupper(int c);
int	ft_strncmp(const char *first, const char *second, size_t length);
long int	ft_strtol(char *nptr, char **end_ptr, int base);
int							philo_init(char *args[4], t_philo_data *data);

#endif
