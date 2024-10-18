#include "../philo.h"

void ft_think(philo *philosophe, bool start)
{
    time_t t_think;
    time_t t_sleep;
    time_t t_eat;

    if (!start)
	    philo_print(&philosophe->table_info->mutex_printf, philosophe, THINK);
    if (philosophe->number_of_philo % 2 == 0)
        return;
    t_eat = philosophe->table_info->time_to_eat;
    t_sleep = philosophe->table_info->time_to_sleep;
    t_think = (t_eat * 2 ) - t_sleep;
    if (t_think < 0)
        t_think = 0;
    if (philosophe->index % 2)
        ft_usleep((size_t)(t_think * 0.42)); // dont want to wait
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
		ft_think(philosophe, false);
}


void take_fork(philo *phil, t_mtx *mtx)
{
	my_mutex_function(LOCK, mtx);
    philo_action(phil, TAKE_FORK);
}