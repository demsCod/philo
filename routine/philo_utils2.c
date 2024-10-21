/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:41:05 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/21 00:26:52 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_eat(t_philo *phil)
{
	time_t	time;
	long	i;

	time = get_time_in_ms() - phil->table_info->time;
	i = get_long(&phil->mutex_meal_count, &phil->eat_counters);
	++i;
	printf(BOLDGREEN "%ld      %d is eating\n" RESET, time, phil->index);
	set_long(&phil->mutex_meal_count, &phil->eat_counters, i);
	if (phil->table_info->extra_args
		&& i == get_long(&phil->table_info->mutex_meal_count,
			&phil->table_info->limit_eat))
		set_bool(&phil->mutex_meal_count, &phil->full, true);
}

void	philo_print(t_mtx *mtx, t_philo *phil, int action)
{
	time_t	time;

	my_mutex_function(LOCK, mtx);
	if (get_bool(&phil->table_info->mutex_checking, &phil->table_info->end))
	{
		my_mutex_function(UNLOCK, mtx);
		return ;
	}
	time = get_time_in_ms() - phil->table_info->time;
	if (action == TAKE_FORK)
		printf("%ld      %d has taken a fork\n", time, phil->index);
	else if (action == EAT)
		ft_print_eat(phil);
	else if (action == SLEEP)
	{
		time = get_time_in_ms() - phil->table_info->time;
		printf("%ld      %d is sleeping\n", time, phil->index);
	}
	else if (action == THINK)
	{
		time = get_time_in_ms() - phil->table_info->time;
		printf("%ld      %d is thinking\n", time, phil->index);
	}
	my_mutex_function(UNLOCK, mtx);
}
