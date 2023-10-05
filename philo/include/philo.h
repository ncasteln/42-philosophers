/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:55:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/05 09:49:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>	// printf()
# include <sys/time.h>
# include <stdio.h>
# include <string.h>	// memset used in ft_calloc
// # include <libc.h>	// memset used in ft_calloc

// error definitions
# define EARGC				1
# define EMALLOC			2
# define ECREATE_THREAD		3
# define ETHJOIN			4
# define EMUTEX_INIT		5
# define EMUTEX_DESTROY		6
# define ECREATE_PHILO		7
# define EGET_TIME			8

// action definition
typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
	ENOUGH
}			t_action;

typedef struct s_shared_info
{
	int64_t		clock_start;
	int			someone_is_dead;
	int			everyone_has_eaten;
}				t_shared_info;

typedef struct s_time
{
	int			to_die;
	int			to_eat;
	int			to_sleep;
	int			eat_limit;
	int64_t		clock_start;		// to be intended like the internal clock
	int			someone_is_dead;
	int			everyone_has_eaten;
}				t_time;

typedef struct s_philo
{
	int				id;
	struct s_time	*time;			// ???? dont need so much
	int				last_eat;
	int				start_sleeping;
	int				start_thinking;
	int				end_thinking;	// --------------------------------------------- necessary ?????
	int				is_turn;		// [0] start - [1] queued
	int				n_eat;			// n of times the philo eats
	pthread_mutex_t	*fork[2];		// access to mutual exclusion of the forks
}				t_philo;

typedef struct s_monastery
{
	int				n_philo;
	struct s_philo	**philo;
	struct s_time	*time;
	pthread_t		*th_philo;
	pthread_t		th_dead_monitor;
	pthread_t		th_eat_monitor;
	int				*n_eat_status;	// n of times each philo has eaten
	pthread_mutex_t	*forks;			// n of mutex == n_philo
	int				err_code;
}				t_monastery;

// -------------------------------------------------------------------- PARSING
int		create_monastery(t_monastery *data, char **argv);
t_philo	**create_philo(t_monastery *data);

// -------------------------------------------------------------------- THREADS
int		create_threads(t_monastery *data);
int		join_threads(t_monastery *data);
void	*philo_routine(void *arg);
void	*dead_routine(void *arg);
void	*eat_routine(void *arg);

// ----------------------------------------------------------------------- TIME
int64_t	get_time_ms(void);
int64_t	now(int64_t clock_start);
void	accurate_sleep(int64_t n);

// ---------------------------------------------------------------------- UTILS
int		ft_atoi(const char *str);
void	*ft_calloc(size_t len, size_t n_bits);

// ---------------------------------------------------------------- PRINT UTILS
int		error(int *err_store, int err_code, char *file, int line);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	print_single_philo(t_philo *philo);
void	print_all_philo(t_philo **philo);
void	print_tmstmp(int who, t_action what, int64_t clock_start);

#endif
