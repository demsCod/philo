/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:37:18 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/20 23:14:29 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_free(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_phil_list(t_philo **phil)
{
	t_philo	*current;
	t_philo	*next;
	t_philo	*last;

	if (phil == NULL || *phil == NULL)
		return ;
	current = *phil;
	last = current;
	while (last->next != *phil)
		last = last->next;
	last->next = NULL;
	while (current != NULL)
	{
		next = current->next;
		my_mutex_function(DESTROY, &current->fork);
		my_mutex_function(DESTROY, &current->mutex_meal_time);
		my_mutex_function(DESTROY, &current->mutex_meal_count);
		my_mutex_function(DESTROY, &current->ph_mutex);
		free(current);
		current = next;
	}
	*phil = NULL;
}

void	free_and_exit(t_table *full_data)
{
	free_phil_list(&full_data->philo);
	my_mutex_function(DESTROY, &full_data->mutex_printf);
	my_mutex_function(DESTROY, &full_data->mutex_checking);
	my_mutex_function(DESTROY, &full_data->mutex_meal_time);
	my_mutex_function(DESTROY, &full_data->mutex_meal_count);
	my_mutex_function(DESTROY, &full_data->mutex_calcul_think_time);
	my_mutex_function(DESTROY, &full_data->mutex_dead);
	my_mutex_function(DESTROY, &full_data->mutex_ready);
	free(full_data);
}
