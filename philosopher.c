/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:02:16 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/15 22:09:44 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "philo.h"

int parse_data (char **data, philo **phil)
{
	int number_of_philo;
	int	index;
	philo *last;
	t_table			*table;


	index = 1;
	number_of_philo = ft_atoi(data[0]);
	table = init_table_info(data);
	while (number_of_philo > 0)
	{
		add_philo_back(phil, index, table);
		number_of_philo--;
		index++;
	}
	(*phil)->number_of_philo = ft_atoi(data[0]);
	last = last_philo(phil);
	last->next = *phil;
	return (0);
}

int main(int ac, char **av)
{
	philo *philo;

	if (ac == 5)
	{
		philo = malloc(sizeof(philo));
		philo = NULL;
		if (parse_data(av + 1, &philo) == 1)
			return (0);
		if (routine_philo(&philo) == 1)
			exit(0);
	}
	else
		return (0);
}