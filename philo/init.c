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

static int	init_forks(t_table *t)
{
	int	i;

	t->forks = malloc(sizeof(pthread_mutex_t) * t->n);
	if (!t->forks)
		return (-1);
	i = 0;
	while (i < t->n)
	{
		if (pthread_mutex_init(&t->forks[i], NULL) != 0)
			return (-1);
		t->forks_inited++;
		i++;
	}
	return (0);
}

static int	init_philo(t_philo *p, int id, long start_ms, t_table *t)
{
	p->id = id;
	p->meal_count = 0;
	p->last_meal_ms = start_ms;
	p->table = t;
	p->left_fork = &t->forks[id - 1];
	p->right_fork = &t->forks[id % t->n];
	if (pthread_mutex_init(&p->meal_lock, NULL) != 0)
		return (-1);
	return (0);
}

static int	init_philos(t_table *t)
{
	int	i;

	t->philos = malloc(sizeof(t_philo) * t->n);
	if (!t->philos)
		return (-1);
	i = 0;
	while (i < t->n)
	{
		if (init_philo(&t->philos[i], i + 1, t->start_ms, t) != 0)
			return (-1);
		t->meal_locks_inited++;
		i++;
	}
	return (0);
}

int	init_table(t_table *t)
{
	t->start_ms = get_time_ms();
	t->stopped = 0;
	t->forks_inited = 0;
	t->meal_locks_inited = 0;
	t->stop_lock_inited = 0;
	t->print_lock_inited = 0;
	if (init_forks(t) != 0)
		return (-1);
	if (init_philos(t) != 0)
		return (-1);
	if (pthread_mutex_init(&t->stop_lock, NULL) != 0)
		return (-1);
	t->stop_lock_inited = 1;
	if (pthread_mutex_init(&t->print_lock, NULL) != 0)
		return (-1);
	t->print_lock_inited = 1;
	return (0);
}
