/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:43:04 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/20 23:22:23 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*last_philo(t_philo **lst)
{
	t_philo	*current;

	current = (*lst);
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

void	add_philo_back(t_philo **lst, int index, t_table *table)
{
	t_philo	*last;
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	ft_memset(new, 0, sizeof(t_philo));
	new->index = index;
	new->table_info = table;
	if (!*lst)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	last = last_philo(lst);
	last->next = new;
}

t_table	*init_table_info(char **data)
{
	t_table	*table_info;

	table_info = malloc(sizeof(t_table));
	ft_memset(table_info, 0, sizeof(t_table));
	table_info->time_to_die = ft_atoi(data[1]);
	table_info->time_to_eat = ft_atoi(data[2]);
	table_info->time_to_sleep = ft_atoi(data[3]);
	return (table_info);
}

void	print_table(t_philo **lst)
{
	t_philo	*temp;

	temp = (*lst);
	while (temp != NULL)
	{
		printf("[%d]->", temp->index);
		temp = temp->next;
	}
}
