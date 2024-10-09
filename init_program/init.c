/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:43:04 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/09 18:47:04 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


philo	*last_philo(philo *lst)
{
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}


void	add_philo_back(philo **lst, int index)
{
	philo	*last;
	philo 	*new;

	new = malloc(sizeof(philo));
	ft_memset(new, 0, sizeof(philo));
	new->index = index;
	if (!*lst)
	{
		*lst = new;
		printf(" o %d\n", new->index);
		return ;
	}
	last = last_philo((*lst));
	last->next = new;
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