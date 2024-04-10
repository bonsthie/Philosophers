/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:20:25 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/10 14:50:16 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define MAX_INT 0x7FFFFFFF

typedef pthread_mutex_t		t_pthread_mutex;

typedef unsigned long int	t_pthread;

typedef enum e_status
{
	NOTHING,
	EAT,
	THINK,
	SLEEP,
}							t_status;

typedef struct s_time
{
	int						eat;
	int						sleep;
	int						die;
}							t_time;

typedef struct s_philo
{
	t_pthread				thread;
	t_pthread_mutex			fork_left;
	t_pthread_mutex			*fork_right;
	t_status				status;
	long long				time_status;
	long long				last_ate;
	int						id;
}							t_philo;

typedef struct s_philo_data
{
	t_philo					*philo;
	t_time					time;
	int						philo_nb;
}							t_philo_data;

typedef struct s_thread_arg
{
	t_philo					*philo;
	t_time					time;
	t_pthread_mutex			*mutex_print;
}							t_thread_arg;

// function
int							philo_init(char *args[4], t_philo_data *data);
void *philo_routine(void *args);

// mutex utils
void						mutex_destroy(t_philo_data *data);
void						mutex_init(t_philo_data *data);

// utils function
int							ft_isdigit(int c);
int							ft_isspace(int c);
int							ft_toupper(int c);
long int					ft_strtol(char *nptr, char **end_ptr, int base);
int							ft_strncmp(const char *first, const char *second,
								size_t length);


int ft_putstr(const char *str);
void  __attribute__ ((format (printf, 1, 0)))
print_status(char *str, t_pthread_mutex *mutex, long long int time, int philo_id);
#endif
