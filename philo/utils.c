/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:19:48 by peda-cos          #+#    #+#             */
/*   Updated: 2025/02/16 12:22:31 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mini_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)result);
}

long long	get_current_time(void)
{
	struct timeval	tv;
	long long		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (time_in_ms);
}

void	print_message(t_philo *philo, char *msg)
{
	long long	time;
	int			sim_end;

	pthread_mutex_lock(&philo->data->end_mutex);
	sim_end = philo->data->simulation_end;
	pthread_mutex_unlock(&philo->data->end_mutex);
	if (sim_end)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_current_time() - philo->data->start_time;
	printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	print_death_message(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_current_time() - philo->data->start_time;
	printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
