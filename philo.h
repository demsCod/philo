/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:27:24 by mdembele          #+#    #+#             */
/*   Updated: 2024/10/22 21:51:57 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define IS_DEAD 1

# include "libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define TAKE_FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
/***************** */

# define LOCK 1
# define UNLOCK 2
# define INIT 3
# define DESTROY 4

# define RESET "\033[0m"
# define BLACK "\033[30m"              /* Black */
# define RED "\033[31m"                /* Red */
# define GREEN "\033[32m"              /* Green */
# define YELLOW "\033[33m"             /* Yellow */
# define BLUE "\033[34m"               /* Blue */
# define MAGENTA "\033[35m"            /* Magenta */
# define CYAN "\033[36m"               /* Cyan */
# define WHITE "\033[37m"              /* White */
# define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
# define BOLDRED "\033[1m\033[31m"     /* Bold Red */
# define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
# define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
# define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
# define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
# define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

typedef pthread_mutex_t	t_mtx;

typedef struct t_table
{
	bool				end;
	bool				extra_args;
	bool				ready;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	time_t				time_to_die;
	time_t				time;
	time_t				time_to_think;
	int					number_of_philo;
	time_t				limit_eat;
	struct t_philo		*philo;
	t_mtx				mutex_printf;
	t_mtx				mutex_checking;
	t_mtx				mutex_meal_time;
	t_mtx				mutex_meal_count;
	t_mtx				mutex_calcul_think_time;
	t_mtx				mutex_dead;
	t_mtx				mutex_ready;

}						t_table;

typedef struct t_philo
{
	int					index;
	int					number_of_philo;
	long				eat_counters;
	time_t				last_eat;
	t_mtx				fork;
	t_mtx				mutex_meal_time;
	t_mtx				mutex_meal_count;
	t_mtx				ph_mutex;
	t_table				*table_info;
	struct t_philo		*next;
	bool				died;
	bool				full;
}						t_philo;

void					add_philo_back(t_philo **lst, int index,
							t_table *table);
void					print_table(t_philo **lst);
t_philo					*last_philo(t_philo **lst);
int						routine_philo(t_philo **philo_list);
void					take_fork(t_philo *phil, t_mtx *mtx);
void					my_mutex_function(int FLAG, t_mtx *mtx);
void					philo_action(t_philo *philosophe, int action);
void					philo_print(t_mtx *mtx, t_philo *phil, int action);
t_table					*init_table_info(char **data);
time_t					get_time_in_ms(void);
bool					is_philo_die(t_philo *philosophe);
bool					get_bool(t_mtx *mtx, bool *value);
void					set_long(t_mtx *mtx, long *dest, long src);
void					set_bool(t_mtx *mtx, bool *dest, bool src);
long					get_long(t_mtx *mtx, long *value);
void					de_synchronize_philo(t_philo *phi);
void					ft_think(t_philo *philosophe, bool start);
int						ft_usleep(size_t milliseconds, t_philo *phil,
							bool thread);
void					free_and_exit(t_table *full_data);
void					*begin_routine(void *phi);
int						check_monitor_helper(t_table *table,
							t_philo **philo_list, int *i);
void					wait_is_ready(t_mtx *mtx, bool *ready);
void					eat_left(t_philo *philosophe);
void					eat_right(t_philo *philosophe);
void					print_death(t_table *table, t_philo *philo_list);
void					init_routine(t_table *table);
void					hardcode_philo(t_philo *philo);

#endif