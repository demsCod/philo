/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:02:16 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/16 23:39:01 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "philo.h"

int parse_data (char **data, philo **phil, int ac)
{
	int number_of_philo;
	int	index;
	philo *last;
	t_table			*table;


	index = 1;
	number_of_philo = ft_atoi(data[0]);
	table = init_table_info(data);
	table->number_of_philo = number_of_philo;
	if (ac == 6)
	{
		table->limit_eat =  ft_atoi(data[4]);
		table->extra_args = true;
	}
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

int is_only_numbers(char *av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if(ft_isalnum(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int check_input(char *av)
{
	int check;
	
	if (is_only_numbers(av))
	{
		check = ft_atoi(av);
		if (check < 0)
		{
			ft_putendl_fd("Error : philo not takes alphabectics or negative args", 2);
			return (0);
		}
		return (1);
	}
	ft_putendl_fd("Error : philo not takes alphabectics or negative args", 2);
	return (0);
}
void check_valids_args(char **av, int ac)
{
	int check;
	int i;
	
	(void)ac;
	if (is_only_numbers(av[0]))
	{
		check = ft_atoi(av[0]);
		if (check > 200 || check <= 0)
		{
			ft_putendl_fd("Error : the numbers of philo input should be minor than 200 or bigger than 0", 2);
			exit (1);
		}
	}
	else
		exit(1);
	i = 1;
	while (i < ac - 1)
	{
		if (check_input(av[i]) == 0)
			exit (1);
		i++;
	}
}

int main(int ac, char **av)
{
	philo *philo;

	if (ac == 5 || ac == 6)
	{
		philo = malloc(sizeof(philo));
		if (!philo)
			return (1);
		philo = NULL;
		check_valids_args(av + 1, ac);
		if (parse_data(av + 1, &philo, ac) == 1)
			return (1);
		if (routine_philo(&philo) == 1)
			exit(1);
	}
	else
		return (1);
}