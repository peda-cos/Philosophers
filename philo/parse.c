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

#include "philo.h"
#include <limits.h>

int	parse_long(const char *s, long *out)
{
	long	result;

	result = 0;
	if (!s || !*s)
		return (-1);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (-1);
		result = result * 10 + (*s - '0');
		if (result > INT_MAX)
			return (-1);
		s++;
	}
	*out = result;
	return (0);
}

static int	check_ranges(t_table *table)
{
	if (table->n < 1 || table->n > 200)
		return (-1);
	if (table->t_die < 1 || table->t_eat < 1 || table->t_sleep < 1)
		return (-1);
	if (table->meals_required != -1 && table->meals_required < 1)
		return (-1);
	return (0);
}

static int	parse_err(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	write(2, msg, i);
	write(2, "\n", 1);
	return (-1);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	long	tmp;

	if (argc != 5 && argc != 6)
		return (parse_err("Error: usage: philo n t_die t_eat t_sleep [meals]"));
	if (parse_long(argv[1], &tmp) == -1)
		return (parse_err("Error: invalid argument"));
	table->n = (int)tmp;
	if (parse_long(argv[2], &table->t_die) == -1)
		return (parse_err("Error: invalid argument"));
	if (parse_long(argv[3], &table->t_eat) == -1)
		return (parse_err("Error: invalid argument"));
	if (parse_long(argv[4], &table->t_sleep) == -1)
		return (parse_err("Error: invalid argument"));
	table->meals_required = -1;
	if (argc == 6)
	{
		if (parse_long(argv[5], &tmp) == -1)
			return (parse_err("Error: invalid argument"));
		table->meals_required = (int)tmp;
	}
	if (check_ranges(table) == -1)
		return (parse_err("Error: argument out of range"));
	return (0);
}
