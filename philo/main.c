/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:59:28 by peda-cos          #+#    #+#             */
/*   Updated: 2025/02/06 01:59:01 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor_philos(t_philo *philos, t_data *data)
{
	int			i;
	long long	current_time;
	int			finished;

	while (1)
	{
		i = 0;
		finished = 0;
		while (i < data->number_of_philosophers)
		{
			current_time = get_time();
			pthread_mutex_lock(&data->simulation_mutex);
			if (current_time - philos[i].last_meal > data->time_to_die)
			{
				print_message(&philos[i], "died");
				data->simulation_end = 1;
				pthread_mutex_unlock(&data->simulation_mutex);
				return ;
			}
			if (data->must_eat != -1 && philos[i].meals_eaten >= data->must_eat)
				finished++;
			pthread_mutex_unlock(&data->simulation_mutex);
			i++;
		}
		if (data->must_eat != -1 && finished == data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->simulation_mutex);
			data->simulation_end = 1;
			pthread_mutex_unlock(&data->simulation_mutex);
			return ;
		}
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;
	int		i;

	if (argc < 5)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (init_data(&data, argc, argv))
		return (1);
	philos = init_philos(&data);
	if (!philos)
		return (1);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	monitor_philos(philos, &data);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (0);
}
