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

static void	close_meal_sems(t_table *table)
{
	char	name[32];
	int		i;

	i = 0;
	while (i < table->n)
	{
		if (table->philos[i].meal_sem)
			sem_close(table->philos[i].meal_sem);
		build_sem_name("/philo_meal_", table->philos[i].id, name, sizeof(name));
		sem_unlink(name);
		i++;
	}
}

static void	close_turn_sems(t_table *table)
{
	char	name[32];
	int		i;

	i = 0;
	while (i < table->n)
	{
		if (table->philos[i].turn_sem)
			sem_close(table->philos[i].turn_sem);
		build_sem_name("/philo_turn_", table->philos[i].id, name, sizeof(name));
		sem_unlink(name);
		i++;
	}
}

void	cleanup_table(t_table *table)
{
	if (!table)
		return ;
	if (table->forks)
	{
		sem_close(table->forks);
		sem_unlink("/philo_forks");
	}
	if (table->print_sem)
	{
		sem_close(table->print_sem);
		sem_unlink("/philo_print");
	}
	if (table->philos)
	{
		close_meal_sems(table);
		close_turn_sems(table);
		free(table->philos);
		table->philos = NULL;
	}
}
