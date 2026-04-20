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

void	print_state(t_philo *philo, char *state)
{
	long	ts;

	sem_wait(philo->table->print_sem);
	ts = get_time_ms() - philo->table->start_ms;
	printf("%ld %d %s\n", ts, philo->id, state);
	sem_post(philo->table->print_sem);
}

int	build_sem_name(char *prefix, int id, char *out, int cap)
{
	char	tmp[12];
	int		i;
	int		j;
	int		d;

	i = 0;
	j = 0;
	while (prefix[j] && i < cap - 1)
		out[i++] = prefix[j++];
	d = 0;
	if (id == 0)
		tmp[d++] = '0';
	while (id > 0)
	{
		tmp[d++] = '0' + (id % 10);
		id /= 10;
	}
	if (i + d >= cap)
		return (-1);
	while (d > 0)
		out[i++] = tmp[--d];
	out[i] = '\0';
	return (0);
}
