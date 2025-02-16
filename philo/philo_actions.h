/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:47:50 by peda-cos          #+#    #+#             */
/*   Updated: 2025/02/16 11:55:17 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ACTIONS_H
# define PHILO_ACTIONS_H

# include "philo.h"

void	philosopher_take_forks(t_philo *philo);
void	philosopher_eat(t_philo *philo);
void	philosopher_release_forks(t_philo *philo);
void	philosopher_sleep(t_philo *philo);
void	philosopher_think(t_philo *philo);

#endif