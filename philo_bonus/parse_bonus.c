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

#include <limits.h>
#include "philo_bonus.h"

static int	parse_long(char *s, long *out)
{
	long	n;
	int		i;

	n = 0;
	i = 0;
	if (!s || !s[0])
		return (-1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		if (n > INT_MAX)
			return (-1);
		i++;
	}
	if (s[i] != '\0' || i == 0)
		return (-1);
	*out = n;
	return (0);
}

static int	parse_times(char **argv, t_table *table)
{
	long	tmp;

	if (parse_long(argv[2], &tmp) || tmp < 1)
		return (-1);
	table->t_die = tmp;
	if (parse_long(argv[3], &tmp) || tmp < 1)
		return (-1);
	table->t_eat = tmp;
	if (parse_long(argv[4], &tmp) || tmp < 1)
		return (-1);
	table->t_sleep = tmp;
	return (0);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	long	tmp;

	if (argc != 5 && argc != 6)
		return (-1);
	if (parse_long(argv[1], &tmp) || tmp < 1)
		return (-1);
	table->n = (int)tmp;
	if (table->n < 1 || table->n > 200)
		return (-1);
	if (parse_times(argv, table))
		return (-1);
	table->meals_required = -1;
	if (argc == 6)
	{
		if (parse_long(argv[5], &tmp) || tmp < 1)
			return (-1);
		table->meals_required = (int)tmp;
	}
	return (0);
}
