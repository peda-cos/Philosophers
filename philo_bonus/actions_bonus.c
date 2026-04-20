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

static int	next_in_chain(int id, int n)
{
	int	next;

	next = id + 2;
	if (next > n)
	{
		if (id % 2 == 0)
			next = 2;
		else
			next = 1;
	}
	return (next);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->turn_sem);
	sem_wait(philo->forks);
	print_state(philo, "has taken a fork");
	sem_wait(philo->forks);
	print_state(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	t_table	*t;
	int		next;

	t = philo->table;
	print_state(philo, "is eating");
	sem_wait(philo->meal_sem);
	philo->last_meal_ms = get_time_ms();
	sem_post(philo->meal_sem);
	ft_sleep(t->t_eat, t);
	sem_post(philo->forks);
	sem_post(philo->forks);
	next = next_in_chain(philo->id, t->n);
	sem_post(t->philos[next - 1].turn_sem);
	sem_wait(philo->meal_sem);
	philo->meal_count++;
	sem_post(philo->meal_sem);
}

void	philo_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_sleep(philo->table->t_sleep, philo->table);
}

void	think(t_philo *philo)
{
	print_state(philo, "is thinking");
}
