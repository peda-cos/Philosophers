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

static int	fork_children(t_table *t)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < t->n)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
		{
			philo_routine(&t->philos[i]);
			exit(0);
		}
		t->philos[i].pid = pid;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (parse_args(argc, argv, &table))
		return (1);
	if (init_table(&table))
		return (1);
	if (fork_children(&table))
		return (1);
	monitor_routine(&table);
	cleanup_table(&table);
	return (0);
}
