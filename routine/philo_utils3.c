/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:45:41 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/22 21:46:28 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_alone(void *philo)
{
	t_philo	*philosophe;

	philosophe = (t_philo *)philo;
	philosophe->table_info->time = get_time_in_ms();
	my_mutex_function(LOCK, &philosophe->fork);
	philo_action(philosophe, TAKE_FORK);
	my_mutex_function(UNLOCK, &philosophe->fork);
	ft_usleep(philosophe->table_info->time_to_die, philo, false);
	my_mutex_function(LOCK, &philosophe->fork);
	printf("\033[0;31m%ld      %i die\033[0m\n", get_time_in_ms()
		- philosophe->table_info->time, philosophe->index);
	my_mutex_function(UNLOCK, &philosophe->fork);
	return (NULL);
}

void	hardcode_philo(t_philo *philo)
{
	pthread_t	thread;
	t_table		*table;

	table = philo->table_info;
	table->philo = philo;
	init_routine(table);
	pthread_mutex_lock(&table->mutex_ready);
	pthread_mutex_init(&philo->fork, NULL);
	pthread_mutex_init(&philo->ph_mutex, NULL);
	my_mutex_function(INIT, &philo->mutex_meal_time);
	my_mutex_function(INIT, &philo->ph_mutex);
	my_mutex_function(INIT, &philo->mutex_meal_count);
	pthread_create(&thread, NULL, philo_alone, philo);
	pthread_mutex_unlock(&table->mutex_ready);
	pthread_join(thread, NULL);
}
