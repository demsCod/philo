#include "../philo.h"

void ft_think(philo *philosophe)
{
    time_t t_think;

    t_think = 0;
	philo_print(&philosophe->table_info->mutex_printf, philosophe, THINK);
    ft_usleep(t_think);
}
void philo_action (philo *philosophe, int action)
{
    if (action == TAKE_FORK)
		philo_print(&philosophe->table_info->mutex_printf, philosophe, TAKE_FORK);
    else if (action == EAT)
    {
        set_long(&philosophe->mutex_meal_time, &philosophe->last_eat, get_time_in_ms() - philosophe->table_info->time);
		philo_print(&philosophe->table_info->mutex_printf, philosophe, EAT);
        ft_usleep(philosophe->table_info->time_to_eat);
    }
    else if (action == SLEEP)
    {
		philo_print(&philosophe->table_info->mutex_printf, philosophe, SLEEP);
        ft_usleep(philosophe->table_info->time_to_sleep);
    }
    else if (action == THINK)
		ft_think(philosophe);
}


void take_fork(philo *phil, t_mtx *mtx)
{
	my_mutex_function(LOCK, mtx);
    philo_action(phil, TAKE_FORK);
}