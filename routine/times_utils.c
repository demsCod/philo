/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:38:07 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/20 23:11:19 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		ft_putendl_fd("gettime failed\n", 2);
		return (0);
	}
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

int	ft_usleep(size_t milliseconds, t_philo *phil, bool phi)
{
	size_t	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < milliseconds)
	{
		if (phi)
		{
			if (get_bool(&phil->ph_mutex, &phil->died))
				return (1);
			if (get_bool(&phil->table_info->mutex_checking,
					&phil->table_info->end))
				return (1);
		}
		usleep(10);
	}
	return (0);
}
