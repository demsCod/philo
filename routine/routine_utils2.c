/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:46:45 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/22 21:48:58 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_is_ready(t_mtx *mtx, bool *ready)
{
	while (get_bool(mtx, ready) == false)
		;
}

void	eat_left(t_philo *philosophe)
{
	take_fork (philosophe, &philosophe->fork);
	take_fork(philosophe, &philosophe->next->fork);
	philo_action(philosophe, EAT);
	my_mutex_function(UNLOCK, &philosophe->fork);
	my_mutex_function(UNLOCK, &philosophe->next->fork);
}

void	eat_right(t_philo *philosophe)
{
	take_fork(philosophe, &philosophe->next->fork);
	take_fork(philosophe, &philosophe->fork);
	philo_action(philosophe, EAT);
	my_mutex_function(UNLOCK, &philosophe->next->fork);
	my_mutex_function(UNLOCK, &philosophe->fork);
}

void	print_death(t_table *table, t_philo *philo_list)
{
	my_mutex_function(LOCK, &table->mutex_printf);
	printf("\033[0;31m%ld      %i die\033[0m\n", get_time_in_ms()
		- table->time, philo_list->index);
	my_mutex_function(UNLOCK, &table->mutex_printf);
	my_mutex_function(UNLOCK, &philo_list->ph_mutex);
}

void	init_routine(t_table *table)
{
	my_mutex_function(INIT, &table->mutex_checking);
	my_mutex_function(INIT, &table->mutex_printf);
	my_mutex_function(INIT, &table->mutex_meal_count);
	my_mutex_function(INIT, &table->mutex_calcul_think_time);
	my_mutex_function(INIT, &table->mutex_dead);
	my_mutex_function(INIT, &table->mutex_ready);
}
