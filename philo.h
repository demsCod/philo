/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:27:24 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/09 18:37:57 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#define IS_DEAD 1

#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct t_philo
{
	int 		index;
	int	 		fork;
	unsigned int time_to_eat;
	unsigned int time_to_sleep;
	unsigned int time_to_think;
	bool is_dead;
	struct t_philo *next;	
}	philo;


#endif