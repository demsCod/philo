#include "../philo.h"

void ft_think(philo *philosophe, bool start)
{
    time_t t_now;
    time_t t_die;
	time_t last_eat;

    if (!start)
	    philo_print(&philosophe->table_info->mutex_printf, philosophe, THINK);
	t_now = get_time_in_ms() - philosophe->table_info->time;
    t_die = philosophe->table_info->time_to_die;
	last_eat = t_now - get_long(&philosophe->mutex_meal_time, &philosophe->last_eat);
	while (last_eat < t_die - 50)
	{
		t_now = get_time_in_ms() - philosophe->table_info->time;
		last_eat = t_now - get_long(&philosophe->mutex_meal_time, &philosophe->last_eat);
		ft_usleep(1.);
	}
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
	(void)mtx;
	// my_mutex_function(LOCK, mtx);
    philo_action(phil, TAKE_FORK);
}