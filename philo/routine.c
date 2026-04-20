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

#include "philo.h"

static long	get_delay(t_table *t)
{
	long	delay;

	delay = t->t_eat - 10;
	if (t->t_eat / 2 < delay)
		delay = t->t_eat / 2;
	if (delay < 1)
		delay = 1;
	return (delay);
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	ft_sleep(philo->table->t_die + 1, philo->table);
	pthread_mutex_unlock(philo->left_fork);
}

static void	run_cycle(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	if (!take_forks(philo, first, second))
		return ;
	eat(philo);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	if (is_stopped(philo->table))
		return ;
	philo_sleep(philo);
	if (is_stopped(philo->table))
		return ;
	think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*t;

	philo = (t_philo *)arg;
	t = philo->table;
	if (t->n == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_sleep(get_delay(t), t);
	while (!is_stopped(t))
		run_cycle(philo);
	return (NULL);
}
