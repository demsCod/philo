/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:27:24 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/16 23:38:34 by mdembele         ###   ########.fr       */
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
/***************** */

# define LOCK   	1
# define UNLOCK 	2
# define INIT		3
# define DESTROY	4

typedef pthread_mutex_t  t_mtx;

typedef struct t_table
{
	bool end;
	bool extra_args;
	time_t time_to_eat;
	time_t time_to_sleep;
	time_t time_to_die;
	time_t     time;
	time_t time_to_think;
	int          number_of_philo;
	int			 limit_eat;
	struct t_philo		*philo;
	pthread_t	 *monitor;
	t_mtx		 mutex_printf;
	t_mtx		 mutex_checking;
	t_mtx		 mutex_meal_time;
	t_mtx		 mutex_init_time;
	t_mtx		 mutex_meal_count;
	t_mtx		 mutex_calcul_think_time;
	t_mtx		 mutex_dead;



} t_table;


typedef struct t_philo
{
	int 		index;
	int			number_of_philo;
	int 		eat_counters;
	time_t		last_eat;
	t_mtx	 	*fork;
	t_mtx 		mutex_meal_time;
	t_table 	*table_info;
	struct t_philo *next;	
	bool		died;
	bool 		full;
}	philo;


void	add_philo_back(philo **lst, int index,  t_table *);
void 	print_table(philo **lst);
philo	*last_philo(philo **lst);
int 	routine_philo (philo **philo_list);
void 	take_fork(philo *phil, t_mtx *mtx);
void	my_mutex_function(int FLAG, t_mtx *mtx);
void 	philo_action (philo *philosophe, int action);
void 	philo_print(t_mtx *mtx, philo *phil, int action);
t_table	*init_table_info(char **data);
time_t	get_time_in_ms(void);
bool 	is_philo_die(philo *philosophe);
bool 	get_bool(t_mtx *mtx, bool value);
void 	set_long(t_mtx *mtx, long *dest, long src);
void 	set_bool(t_mtx *mtx, bool *dest, bool src);
long 	get_long(t_mtx *mtx, long *value);
void de_synchronize_philo(philo *phi);
void ft_think(philo *philosophe);

int	ft_usleep(size_t milliseconds);

#endif