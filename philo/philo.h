/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:58:54 by peda-cos          #+#    #+#             */
/*   Updated: 2025/02/16 19:26:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
	int				simulation_end;
}					t_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meals_eaten;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
}					t_philo;

void				philosopher_take_forks(t_philo *philo);
void				philosopher_eat(t_philo *philo);
void				philosopher_release_forks(t_philo *philo);
void				philosopher_sleep(t_philo *philo);
void				philosopher_think(t_philo *philo);

int					initialize_simulation_data(t_data *data, int argc,
						char **argv);
t_philo				*initialize_philosophers(t_data *data);
void				cleanup_simulation(t_data *data, t_philo *philos);

void				monitor_philosophers(t_philo *philos, t_data *data);

void				*philosopher_routine(void *arg);

int					mini_atoi(const char *str);
long long			get_current_time(void);
void				print_message(t_philo *philo, char *msg);
void				print_death_message(t_philo *philo, char *msg);

#endif
