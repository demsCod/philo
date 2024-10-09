/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:02:16 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/09 18:44:15 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "philo.h"




int parse_data (char **data, philo *philo)
{
	int number_of_philo;
	int	index;
	
	index = 0;
	number_of_philo = atoi(data[0]);
	while (number_of_philo > 0)
	{
		//init_philo(philo, char **data,  index);
		number_of_philo--;
		index++;
	}
	return (0);
}

int main(int ac, char **av)
{
	philo philo;
	if (ac == 5)
	{
		if (parse_data(av + 1, &philo) == 1)
			return (0);
	}
	else
		return (0);
}