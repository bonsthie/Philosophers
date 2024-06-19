/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:20:25 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/19 15:55:53 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/cdefs.h>
# include <unistd.h>

typedef pthread_mutex_t		t_mutex;

typedef unsigned long int	t_pthread;

typedef struct s_philo_data	t_philo_data;

typedef struct s_time
{
	long long				eat;
	long long				sleep;
	long long				die;
}							t_time;

typedef struct s_philo
{
	t_pthread				thread;
	t_mutex					fork_left;
	t_mutex					*fork_right;
	t_philo_data			*data;
	long long				last_ate;
	int						eat_count;
	int						id;
}							t_philo;

struct						s_philo_data
{
	t_philo					*philo;
	t_time					time;
	int						stop;
	int						philo_nb;
};

# define MAX_INT 0x7FFFFFFF
# define MICROSECOND 1000000
# define NO_EAT_COUNT -2

# ifndef PTHREAD_SUCCESS
#  define PTHREAD_SUCCESS 0
# endif

# ifndef WAIT_INTERVAL
#  define WAIT_INTERVAL 100
# endif

# define FORK_MSG "\x1b[36m%lld %d has taken a fork\n\x1b[0m"
# define SLEEP_MSG "\x1b[35m%lld %d is sleeping\n\x1b[0m"
# define THINK_MSG "\x1b[32m%lld %d is thinking\n\x1b[0m"
# define EAT_MSG "\x1b[33m%lld %d is eating\n\x1b[0m"
# define DIED_MSG "\x1b[31m%lld %d died\n\x1b[0m"

void						print_status(char *str,
								t_philo_data *data,
								long long int time,
								int philo_id)
							__attribute__((format(printf, 1, 0)));

// function
int							philo_init(char *args[4], t_philo_data *data);
void						*philo_routine(void *args);
int							philo_wait(t_philo *philo, long long time_to_sleep,
								long long time_to_die);
int							stop(int *stop, int f(int *));

// time
int							philo_wait(t_philo *philo, long long time_to_sleep,
								long long time_to_die);
long long					time_reamaning(t_philo *philo);
long long					get_current_time(void);
long long					get_time(void);
int							set_to_stop(int *stop);
int							get_stop_value(int *stop);
int							decrement_stop(int *stop);
void						philo_finish(t_philo_data *data);

// mutex utils
void						mutex_init(t_philo_data *data);
void						*philo_die(t_philo *philo);

// utils function
int							ft_isdigit(int c);
int							ft_isspace(int c);
int							ft_toupper(int c);
long long					ft_strtoll(char *nptr, char **end_ptr, int base);
int							ft_strncmp(const char *__restrict first,
								const char *__restrict second, size_t length);

#endif
