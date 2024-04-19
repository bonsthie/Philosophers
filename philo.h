/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:20:25 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/19 16:50:30 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef pthread_mutex_t		t_mutex;

typedef unsigned long int	t_pthread;

typedef struct s_philo_data	t_philo_data;

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
	t_mutex					fork_left;
	t_mutex					*fork_right;
	t_philo_data			*data;
	t_status				status;
	long long				time_status;
	long long				last_ate;
	int						id;
}							t_philo;

struct						s_philo_data
{
	t_philo					*philo;
	bool					stop;
	t_time					time;
	t_mutex					print_mutex;
	int						philo_nb;
};

# define MAX_INT 0x7FFFFFFF

# ifndef PTHREAD_CANCELED
#  define PTHREAD_CANCELED	((void *)-1)
# endif

# ifndef PTHREAD_SUCCESS
#  define PTHREAD_SUCCESS	((void *)0)
# endif

# ifndef WAIT_INTERVAL 
#  define WAIT_INTERVAL 1000000
# endif

# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[35m"
# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define BEIGE	"\x1b[36m"
# define RESET	"\x1b[0m"

# define ERROR_CREATE	"error [while creating the thread of the %d philo]\n"
# define ERROR_JOIN		"error [while joining thread]\n"

# define FORK_MSG	BEIGE	"%d philo %d has taken a fork\n"	RESET
# define SLEEP_MSG	BLUE	"%d philo %d is sleeping\n"			RESET
# define THINK_MSG	GREEN	"%d philo %d is think\n"			RESET
# define EAT_MSG	YELLOW	"%d philo %d is eat\n"				RESET
# define DIED_MSG	RED		"%d philo %d died\n"				RESET

# ifndef __GNUC__
#  define __PRINTF
# elif !defined(__clang__)
#  define __PRINTF 
# else
#  define __PRINTF  __attribute__((format(printf, 1, 0))) 
# endif

void		print_status(char *str, t_philo_data *data, long long int time,
			int philo_id) __PRINTF;

// function
int			philo_init(char *args[4], t_philo_data *data);
void		*philo_routine(void *args);
int			philo_wait(t_philo *philo, int time_to_sleep, int time_to_die);

// mutex utils
void		mutex_destroy(t_philo_data *data);
void		mutex_init(t_philo_data *data);

// utils function
int			ft_isdigit(int c);
int			ft_isspace(int c);
int			ft_toupper(int c);
long int	ft_strtol(char *__restrict nptr, char **__restrict end_ptr,
				int base) __nonnull((1));
int			ft_strncmp(const char *__restrict first,
				const char *__restrict second,
				size_t length) __nonnull((1, 2));

#endif
