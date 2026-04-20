/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/20 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>

# define MONITOR_POLL_US 500
# define SLEEP_POLL_US 500

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			meal_count;
	long		last_meal_ms;
	pid_t		pid;
	sem_t		*meal_sem;
	sem_t		*forks;
	sem_t		*turn_sem;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int			n;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	int			meals_required;
	long		start_ms;
	sem_t		*print_sem;
	sem_t		*forks;
	t_philo		*philos;
}	t_table;

/* parse_bonus.c */
int		parse_args(int argc, char **argv, t_table *table);

/* init_bonus.c */
int		init_table(t_table *table);

/* cleanup_bonus.c */
void	cleanup_table(t_table *table);

/* time_bonus.c */
long	get_time_ms(void);
void	ft_sleep(long ms, t_table *table);

/* utils_bonus.c */
void	print_state(t_philo *philo, char *state);
int		build_sem_name(char *prefix, int id, char *out, int cap);

/* actions_bonus.c */
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

/* routine_bonus.c */
void	philo_routine(t_philo *philo);

/* monitor_bonus.c */
void	*monitor_thread(void *arg);
void	monitor_routine(t_table *table);

#endif
