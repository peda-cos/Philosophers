/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 01:15:33 by peda-cos          #+#    #+#             */
/*   Updated: 2025/02/16 12:32:33 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_philosopher_actions(t_philo *philo)
{
	philosopher_take_forks(philo);
	philosopher_eat(philo);
	philosopher_release_forks(philo);
	philosopher_sleep(philo);
	philosopher_think(philo);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->end_mutex);
		if (philo->data->simulation_end)
		{
			pthread_mutex_unlock(&philo->data->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->end_mutex);
		run_philosopher_actions(philo);
		usleep(350);
	}
	return (NULL);
}
