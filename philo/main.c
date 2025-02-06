/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:59:28 by peda-cos          #+#    #+#             */
/*   Updated: 2025/02/06 15:49:06 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '+' && argv[i][j + 1] != '\0')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error: arguments must be positive integers\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	create_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	join_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (validate_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	philos = init_philos(&data);
	if (!philos)
		return (1);
	if (create_threads(philos, &data))
		return (1);
	monitor_philos(philos, &data);
	join_threads(philos, &data);
	cleanup(&data, philos);
	return (0);
}
