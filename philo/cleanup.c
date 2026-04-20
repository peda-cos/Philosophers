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

static void	destroy_meal_locks(t_table *t)
{
	int	i;

	if (!t->philos)
		return ;
	i = 0;
	while (i < t->meal_locks_inited)
	{
		pthread_mutex_destroy(&t->philos[i].meal_lock);
		i++;
	}
}

static void	destroy_forks(t_table *t)
{
	int	i;

	if (!t->forks)
		return ;
	i = 0;
	while (i < t->forks_inited)
	{
		pthread_mutex_destroy(&t->forks[i]);
		i++;
	}
}

void	cleanup_table(t_table *t)
{
	destroy_meal_locks(t);
	destroy_forks(t);
	if (t->print_lock_inited)
		pthread_mutex_destroy(&t->print_lock);
	if (t->stop_lock_inited)
		pthread_mutex_destroy(&t->stop_lock);
	free(t->forks);
	free(t->philos);
	t->forks = NULL;
	t->philos = NULL;
}
