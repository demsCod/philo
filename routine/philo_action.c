/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 23:14:42 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/20 23:16:12 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_think(t_philo *philosophe, bool start)
{
	time_t	t_now;
	time_t	t_die;
	time_t	last_eat;

	if (!start)
		philo_print(&philosophe->table_info->mutex_printf, philosophe, THINK);
	t_die = philosophe->table_info->time_to_die;
	t_now = get_time_in_ms() - philosophe->table_info->time;
	last_eat = t_now - get_long(&philosophe->mutex_meal_time,
			&philosophe->last_eat);
	while (last_eat < (t_die - 50))
	{
		t_now = get_time_in_ms() - philosophe->table_info->time;
		last_eat = t_now - get_long(&philosophe->mutex_meal_time,
				&philosophe->last_eat);
		ft_usleep(10, philosophe, true);
	}
}

void	philo_action(t_philo *philosophe, int action)
{
	if (get_bool(&philosophe->table_info->mutex_checking,
			&philosophe->table_info->end))
		return ;
	if (get_bool(&philosophe->table_info->mutex_meal_count, &philosophe->full))
		return ;
	if (action == TAKE_FORK)
	{
		philo_print(&philosophe->table_info->mutex_printf, philosophe,
			TAKE_FORK);
		return ;
	}
	else if (action == EAT)
	{
		set_long(&philosophe->mutex_meal_time, &philosophe->last_eat,
			get_time_in_ms() - philosophe->table_info->time);
		philo_print(&philosophe->table_info->mutex_printf, philosophe, EAT);
		ft_usleep(philosophe->table_info->time_to_eat, philosophe, true);
	}
	else if (action == SLEEP)
	{
		philo_print(&philosophe->table_info->mutex_printf, philosophe, SLEEP);
		ft_usleep(philosophe->table_info->time_to_sleep, philosophe, true);
	}
	else if (action == THINK)
		ft_think(philosophe, false);
}

void	take_fork(t_philo *phil, t_mtx *mtx)
{
	my_mutex_function(LOCK, mtx);
	philo_action(phil, TAKE_FORK);
}
