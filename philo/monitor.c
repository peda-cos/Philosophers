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

static void	signal_stop(t_table *t)
{
	pthread_mutex_lock(&t->stop_lock);
	t->stopped = 1;
	pthread_mutex_unlock(&t->stop_lock);
}

static void	announce_death(t_table *t, int id)
{
	long	ts;

	pthread_mutex_lock(&t->print_lock);
	pthread_mutex_lock(&t->stop_lock);
	t->stopped = 1;
	pthread_mutex_unlock(&t->stop_lock);
	ts = get_time_ms() - t->start_ms;
	printf("%ld %d died\n", ts, id);
	pthread_mutex_unlock(&t->print_lock);
}

static int	all_full(t_table *t)
{
	int	i;
	int	count;

	if (t->meals_required == -1)
		return (0);
	i = 0;
	while (i < t->n)
	{
		pthread_mutex_lock(&t->philos[i].meal_lock);
		count = t->philos[i].meal_count;
		pthread_mutex_unlock(&t->philos[i].meal_lock);
		if (count < t->meals_required)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_table	*t;
	int		i;
	long	last;

	t = arg;
	while (!is_stopped(t))
	{
		i = 0;
		while (i < t->n)
		{
			pthread_mutex_lock(&t->philos[i].meal_lock);
			last = t->philos[i].last_meal_ms;
			pthread_mutex_unlock(&t->philos[i].meal_lock);
			if (get_time_ms() - last > t->t_die)
				return (announce_death(t, t->philos[i].id), NULL);
			i++;
		}
		if (all_full(t))
			return (signal_stop(t), NULL);
		usleep(MONITOR_POLL_US);
	}
	return (NULL);
}
