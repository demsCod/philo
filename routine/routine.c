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

int checking_round(t_table *table, t_philo *philo_list, int i)
{
	if (table->extra_args)
	{
		if (get_bool(&philo_list->mutex_meal_count, &philo_list->full))
		{
			if (i == 0)
			{
				set_bool(&table->mutex_checking, &table->end, true);
				my_mutex_function(UNLOCK, &philo_list->ph_mutex);
				return (1);
			}
			my_mutex_function(UNLOCK, &philo_list->ph_mutex);
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

void *check_monitor(t_table *table)
{
    t_philo *philo_list;
    int i;

    i = table->number_of_philo;
    wait_is_ready(&table->mutex_ready, &table->ready);
    philo_list = table->philo;
    while (1)
    {
        if (get_bool(&table->mutex_checking, &table->end))
            return NULL;
        if (check_monitor_helper(table, &philo_list, &i) == 1)
            return NULL;
        ft_usleep(10, philo_list, false);
    }
}

int check_monitor_helper(t_table *table, t_philo **philo_list, int *i)
{
    int check;

    my_mutex_function(LOCK, &(*philo_list)->ph_mutex);
    check = checking_round(table, *philo_list, *i);
    if (check == 8)
    {
        (*i)--;
        my_mutex_function(LOCK, &table->mutex_ready);
        *philo_list = (*philo_list)->next;
        my_mutex_function(UNLOCK, &table->mutex_ready);
        return (0);
    }
    if (check == 1)
        return (1);
    my_mutex_function(UNLOCK, &(*philo_list)->ph_mutex);
    *i = table->number_of_philo;
    my_mutex_function(LOCK, &table->mutex_ready);
    *philo_list = (*philo_list)->next;
    my_mutex_function(UNLOCK, &table->mutex_ready);
    return (0);
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
	while(j < philo->number_of_philo )
		pthread_join(thread_for_phil[j++], NULL);
	free(thread_for_phil);
	return (0);
}

