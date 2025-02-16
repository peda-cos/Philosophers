/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 02:32:02 by peda-cos          #+#    #+#             */
/*   Updated: 2025/02/16 12:04:23 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philosopher_dead(t_philo *philo, t_data *data)
{
	long long	current_time;
	long long	last_meal;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (current_time - last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->simulation_mutex);
		print_message(philo, "died");
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->simulation_mutex);
		return (1);
	}
	return (0);
}

static int	end_simulation_if_all_finished(t_data *data, int finished)
{
	if (data->must_eat != -1 && finished == data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->simulation_mutex);
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->simulation_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_philosophers(t_philo *philos, t_data *data)
{
	int	i;
	int	finished;
	int	meals;

	i = 0;
	finished = 0;
	while (i < data->number_of_philosophers)
	{
		if (is_philosopher_dead(&philos[i], data))
			return (1);
		if (data->must_eat != -1)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			meals = philos[i].meals_eaten;
			pthread_mutex_unlock(&philos[i].meal_mutex);
			if (meals >= data->must_eat)
				finished++;
		}
		i++;
	}
	if (end_simulation_if_all_finished(data, finished))
		return (1);
	return (0);
}

void	monitor_philosophers(t_philo *philos, t_data *data)
{
	while (1)
	{
		if (check_all_philosophers(philos, data))
			break ;
		usleep(1000);
	}
}
