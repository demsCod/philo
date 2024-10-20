/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 23:17:18 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/21 00:40:24 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_is_ready(t_mtx *mtx, bool *ready)
{
	while (get_bool(mtx, ready) == false)
		;
}
void eat_left(t_philo *philosophe)
{
	take_fork(philosophe, &philosophe->fork);
	take_fork(philosophe, &philosophe->next->fork);
	philo_action(philosophe, EAT);
	my_mutex_function(UNLOCK, &philosophe->fork);
	my_mutex_function(UNLOCK, &philosophe->next->fork);
}

void eat_right(t_philo *philosophe)
{
	take_fork(philosophe, &philosophe->next->fork);
	take_fork(philosophe, &philosophe->fork);
	philo_action(philosophe, EAT);
	my_mutex_function(UNLOCK, &philosophe->next->fork);
	my_mutex_function(UNLOCK, &philosophe->fork);
}

void	*begin_routine(void *phi)
{
	t_philo	*philosophe;

	philosophe = (t_philo *)phi;
	wait_is_ready(&philosophe->table_info->mutex_ready,
		&philosophe->table_info->ready);
	set_long(&philosophe->mutex_meal_time, &philosophe->last_eat, 0);
	de_synchronize_philo(philosophe);
	while (1)
	{
		if (get_bool(&philosophe->table_info->mutex_meal_count,
				&philosophe->full))
			break ;
		if (get_bool(&philosophe->ph_mutex, &philosophe->died))
			break ;
		if (get_bool(&philosophe->table_info->mutex_checking,
				&philosophe->table_info->end))
			break ;
		if (philosophe->index % 2 == 0)
			eat_left(philosophe);
		else
			eat_right(philosophe);
		philo_action(philosophe, SLEEP);
		philo_action(philosophe, THINK);
	}
	return (NULL);
}

void print_death (t_table *table, t_philo *philo_list)
{
	my_mutex_function(LOCK, &table->mutex_printf);
	printf("\033[0;31m%ld      %i die\033[0m\n", get_time_in_ms()
			- table->time, philo_list->index);
	my_mutex_function(UNLOCK, &table->mutex_printf);
	my_mutex_function(UNLOCK, &philo_list->ph_mutex);
}

int checking_round(t_table *table, t_philo *philo_list, int i)
{
	if (table->extra_args)
	{
		if (get_bool(&philo_list->mutex_meal_count, &philo_list->full))
		{
			if (i-- == 0)
			{
				set_bool(&table->mutex_checking, &table->end, true);
				my_mutex_function(UNLOCK, &philo_list->ph_mutex);
				return (1);
			}
			my_mutex_function(UNLOCK, &philo_list->ph_mutex);
			my_mutex_function(LOCK, &table->mutex_ready);
			philo_list = philo_list->next;
			my_mutex_function(UNLOCK, &table->mutex_ready);
			return (8);
		}
	}
	if (is_philo_die(philo_list))
	{
		set_bool(&table->mutex_checking, &table->end, true);
		print_death(table, philo_list);
		return (1);
	}
	return (0);
}

void	*check_monitor(t_table *table)
{
	t_philo	*philo_list;
	int	i;
	int check;
	
	i = table->number_of_philo;
	wait_is_ready(&table->mutex_ready, &table->ready);
	philo_list = table->philo;
	while (1)
	{
		if (get_bool(&table->mutex_checking, &table->end))
			return NULL;
		my_mutex_function(LOCK, &philo_list->ph_mutex);
		check = checking_round(table, philo_list, i--);
		if (check == 8)
			continue;
		if (check == 1)
			return (NULL);
		my_mutex_function(UNLOCK, &philo_list->ph_mutex);
		i = table->number_of_philo;
		my_mutex_function(LOCK, &table->mutex_ready);
		philo_list = philo_list->next;
		my_mutex_function(UNLOCK, &table->mutex_ready);
		ft_usleep(10, philo_list, false);
	}
}

void init_routine(t_table *table)
{
	my_mutex_function(INIT, &table->mutex_checking);
	my_mutex_function(INIT, &table->mutex_printf);
	my_mutex_function(INIT, &table->mutex_meal_count);
	my_mutex_function(INIT, &table->mutex_calcul_think_time);
	my_mutex_function(INIT, &table->mutex_dead);
	my_mutex_function(INIT, &table->mutex_ready);
}

void create_thread(int number_philo, t_philo *philo, pthread_t *thread_for_phil)
{
	int	i;

	i = 0;
	while (number_philo > 0)
	{
		pthread_mutex_init(&philo->fork, NULL);
		pthread_mutex_init(&philo->ph_mutex, NULL);
		my_mutex_function(INIT, &philo->mutex_meal_time);
		my_mutex_function(INIT, &philo->ph_mutex);
		my_mutex_function(INIT, &philo->mutex_meal_count);
		pthread_create(&thread_for_phil[i], NULL, begin_routine, philo);
		philo = philo->next;
		number_philo--;
		i++;
	}
}

int	routine_philo(t_philo **philo_list)
{
	pthread_t	*thread_for_phil;
	t_philo		*philo;
	t_table		*table;
	int			j;

	philo = *philo_list;
	table = philo->table_info;
	thread_for_phil = malloc(sizeof(pthread_t) * philo->number_of_philo);
	table->philo = philo;
	init_routine(table);
	pthread_mutex_lock(&table->mutex_ready);
	create_thread(philo->number_of_philo, philo, thread_for_phil);
	table->time = get_time_in_ms();
	table->ready = true;
	pthread_mutex_unlock(&table->mutex_ready);
	check_monitor(table);
	j = 0;
	while (j < philo->number_of_philo )
		pthread_join(thread_for_phil[j++], NULL);
	free(thread_for_phil);
	return (0);
}
