/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:27:24 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/15 23:52:32 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#define IS_DEAD 1

#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "libft/libft.h"
#include <string.h>
#include <pthread.h>

# define TAKE_FORK 	1
# define EAT       	2
# define SLEEP		3
# define THINK		4


typedef pthread_mutex_t  t_mtx;

typedef struct t_table
{
	bool end;
	time_t time_to_eat;
	time_t time_to_sleep;
	time_t time_to_die;
	time_t     time;
	time_t time_to_think;
	int          number_of_philo;
	int			 limit_eat;
	struct t_philo		*philo;
	pthread_t	 *monitor;
	t_mtx		 *mutex_printf;
} t_table;


typedef struct t_philo
{
	int 		index;
	int			number_of_philo;
	int 		eat_counters;
	time_t		last_eat;
	t_mtx	 	*fork;
	t_table 	*table_info;
	struct t_philo *next;	
	bool		died;
	bool 		full;
}	philo;


void	add_philo_back(philo **lst, int index,  t_table *);
void 	print_table(philo **lst);
philo	*last_philo(philo **lst);
int 	routine_philo (philo **philo_list);
t_table *init_table_info(char **data);
#endif