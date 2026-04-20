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

#include "philo_bonus.h"

static void	solo_philo(t_philo *philo)
{
	sem_wait(philo->forks);
	print_state(philo, "has taken a fork");
	ft_sleep(philo->table->t_die + 1, philo->table);
	exit(1);
}

void	philo_routine(t_philo *philo)
{
	t_table		*t;
	pthread_t	mon;

	t = philo->table;
	sem_wait(philo->meal_sem);
	philo->last_meal_ms = get_time_ms();
	sem_post(philo->meal_sem);
	pthread_create(&mon, NULL, monitor_thread, philo);
	pthread_detach(mon);
	if (t->n == 1)
		solo_philo(philo);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
}
