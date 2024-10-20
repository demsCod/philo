/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 23:20:46 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/20 23:21:11 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	is_died(t_philo *phil, t_mtx *mtx)
{
	return (get_bool(mtx, &phil->died));
}

void	de_synchronize_philo(t_philo *phi)
{
	if (phi->index % 2 == 0)
		ft_usleep(10, phi, true);
}

bool	is_philo_die(t_philo *philosophe)
{
	time_t	last_eat;

	last_eat = (get_time_in_ms() - philosophe->table_info->time)
		- get_long(&philosophe->mutex_meal_time, &philosophe->last_eat);
	if (last_eat > philosophe->table_info->time_to_die)
	{
		set_bool(&philosophe->mutex_meal_time, &philosophe->died, true);
		return (true);
	}
	return (false);
}

int	is_end(t_philo *philosophe)
{
	int	end;

	pthread_mutex_lock(&philosophe->table_info->mutex_checking);
	end = philosophe->table_info->end;
	pthread_mutex_unlock(&philosophe->table_info->mutex_checking);
	return (end);
}

int	is_full(t_philo *philosophe)
{
	int	count;

	pthread_mutex_lock(&philosophe->table_info->mutex_checking);
	if (philosophe->table_info->extra_args == false)
	{
		count = 0;
		pthread_mutex_unlock(&philosophe->table_info->mutex_checking);
		return (count);
	}
	count = 0;
	if (philosophe->eat_counters >= philosophe->table_info->limit_eat)
		count = 1;
	pthread_mutex_unlock(&philosophe->table_info->mutex_checking);
	return (count);
}
