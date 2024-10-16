/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:43:04 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/15 22:09:49 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


philo	*last_philo(philo **lst)
{
	philo *current;
	current = (*lst);
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}


void	add_philo_back(philo **lst, int index, t_table *table)
{
	philo	*last;
	philo 	*new;

	new = malloc(sizeof(philo));
	ft_memset(new, 0, sizeof(philo));
	new->index = index;
	new->table_info = table;
	if (!*lst)
	{
		*lst = new;
 		return ;
	}
	last = last_philo(lst);
	last->next = new;
}

/*number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]*/
t_table *init_table_info(char **data)
{
	t_table *table_info;

	table_info = malloc(sizeof(t_table));
	ft_memset(table_info, 0, sizeof(t_table));
	table_info->monitor = malloc(sizeof(pthread_t));
	table_info->time_to_die = ft_atoi(data[1]);                             /**/
	table_info->time_to_eat = ft_atoi(data[2]);
	table_info->time_to_sleep = ft_atoi(data[3]);
    if (table_info->number_of_philo % 2 == 0 && table_info->time_to_eat <= table_info->time_to_sleep)
	    table_info->time_to_think = 0;
	if (table_info->number_of_philo % 2 == 0 && table_info->time_to_eat > table_info->time_to_sleep)
	    table_info->time_to_think = table_info->time_to_eat - table_info->time_to_sleep;
	if (table_info->number_of_philo % 2 != 0 && table_info->time_to_eat == table_info->time_to_sleep)
	    table_info->time_to_think = table_info->time_to_eat;
	if (table_info->number_of_philo % 2 != 0 && table_info->time_to_eat < table_info->time_to_sleep)
	    table_info->time_to_think = table_info->time_to_eat * 2 - table_info->time_to_sleep;
	if (table_info->number_of_philo % 2 != 0 && table_info->time_to_eat > table_info->time_to_sleep)
	    table_info->time_to_think = table_info->time_to_eat * 2 - table_info->time_to_sleep;
	if (table_info->number_of_philo % 2 != 0 && table_info->time_to_eat == table_info->time_to_sleep)
	    table_info->time_to_think = table_info->time_to_eat * 2 - table_info->time_to_sleep;
	return(table_info);
}

void print_table(philo **lst)
{
	philo *temp;

	temp = (*lst);
	while(temp != NULL)
	{
		printf("[%d]->", temp->index);
		temp = temp->next;
	}
}