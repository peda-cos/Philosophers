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

void	*monitor_thread(void *arg)
{
	t_philo	*philo;
	t_table	*t;
	long	last;
	int		count;

	philo = (t_philo *)arg;
	t = philo->table;
	while (1)
	{
		usleep(MONITOR_POLL_US);
		sem_wait(philo->meal_sem);
		last = philo->last_meal_ms;
		count = philo->meal_count;
		sem_post(philo->meal_sem);
		if (get_time_ms() - last > t->t_die)
		{
			print_state(philo, "died");
			exit(1);
		}
		if (t->meals_required != -1 && count >= t->meals_required)
			exit(0);
	}
	return (NULL);
}

static void	kill_all(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n)
	{
		kill(t->philos[i].pid, SIGKILL);
		i++;
	}
}

void	monitor_routine(t_table *table)
{
	int		status;
	int		i;

	i = 0;
	while (i < table->n)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_all(table);
			break ;
		}
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
}
