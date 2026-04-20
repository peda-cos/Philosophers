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

static int	open_sem(char *name, int val, sem_t **out)
{
	sem_unlink(name);
	*out = sem_open(name, O_CREAT | O_EXCL, 0644, val);
	if (*out == SEM_FAILED)
		return (-1);
	return (0);
}

static int	init_meal_sems(t_table *t)
{
	char	name[32];
	int		i;

	i = 0;
	while (i < t->n)
	{
		if (build_sem_name("/philo_meal_", t->philos[i].id, name, sizeof(name)))
			return (-1);
		if (open_sem(name, 1, &t->philos[i].meal_sem))
			return (-1);
		i++;
	}
	return (0);
}

static int	init_turn_sems(t_table *t)
{
	char	name[32];
	int		i;
	int		val;

	i = 0;
	while (i < t->n)
	{
		if (build_sem_name("/philo_turn_", t->philos[i].id, name, sizeof(name)))
			return (-1);
		val = 0;
		if (t->philos[i].id == 1 || t->philos[i].id == 2)
			val = 1;
		if (open_sem(name, val, &t->philos[i].turn_sem))
			return (-1);
		i++;
	}
	return (0);
}

static void	init_philo(t_table *t, int i)
{
	t->philos[i].id = i + 1;
	t->philos[i].meal_count = 0;
	t->philos[i].last_meal_ms = t->start_ms;
	t->philos[i].forks = t->forks;
	t->philos[i].table = t;
	t->philos[i].pid = 0;
}

int	init_table(t_table *table)
{
	int	i;

	table->start_ms = get_time_ms();
	if (open_sem("/philo_forks", table->n, &table->forks))
		return (-1);
	if (open_sem("/philo_print", 1, &table->print_sem))
		return (-1);
	table->philos = malloc(sizeof(t_philo) * table->n);
	if (!table->philos)
		return (-1);
	i = 0;
	while (i < table->n)
	{
		init_philo(table, i);
		i++;
	}
	if (init_meal_sems(table))
		return (-1);
	if (init_turn_sems(table))
		return (-1);
	return (0);
}
