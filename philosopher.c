/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:02:16 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/20 23:13:00 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>

int	parse_data(char **data, t_philo **phil, int ac)
{
	int		number_of_philo;
	int		index;
	t_philo	*last;
	t_table	*table;

	index = 1;
	number_of_philo = ft_atoi(data[0]);
	table = init_table_info(data);
	table->number_of_philo = number_of_philo;
	if (ac == 6)
	{
		table->limit_eat = ft_atoi(data[4]);
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

int	is_only_numbers(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_isalnum(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_input(char *av)
{
	long	check;

	if (is_only_numbers(av))
	{
		check = ft_atoi(av);
		if (check < 0 || check > INT_MAX)
		{
			ft_putendl_fd("Error", 2);
			return (1);
		}
		return (0);
	}
	ft_putendl_fd("Error : philo not takes alphabectics or negative args", 2);
	return (1);
}

int	check_valids_args(char **av, int ac)
{
	long	check;
	int		i;

	(void)ac;
	if (is_only_numbers(av[0]))
	{
		check = ft_atoi(av[0]);
		if (check > 200 || check <= 0)
		{
			ft_putendl_fd("Error", 2);
			return (1);
		}
	}
	else
		return (1);
	i = 1;
	while (i < ac - 1)
	{
		if (check_input(av[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		philo = NULL;
		if (check_valids_args(av + 1, ac))
			return (1);
		if (parse_data(av + 1, &philo, ac) == 1)
			return (1);
		if (routine_philo(&philo) == 1)
			return (1);
		free_and_exit(philo->table_info);
	}
	else
		return (1);
}
