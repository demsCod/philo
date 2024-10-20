#include "../philo.h"

void philo_print(t_mtx *mtx, philo *phil, int action)
{
    time_t time;
    time_t i;

    i = 0;
    my_mutex_function(LOCK, mtx);
    if (get_bool(&phil->table_info->mutex_checking, &phil->table_info->end))
    {
        my_mutex_function(UNLOCK, mtx);
        return ;
    }
    if (action ==  TAKE_FORK)
    {
	    time = get_time_in_ms() - phil->table_info->time;
        printf("%ld      %d has taken a fork\n", time,  phil->index);// 🍴
        my_mutex_function(UNLOCK, mtx);
        return;
    }
    else if (action ==  EAT)
    {
	    time = get_time_in_ms() - phil->table_info->time;
        i = get_long(&phil->mutex_meal_count, &phil->eat_counters);
        ++i;
        printf(BOLDGREEN "%ld      %d is eating\n" RESET, time,  phil->index);//  🍝
        set_long(&phil->mutex_meal_count, &phil->eat_counters, i);
        if (phil->table_info->extra_args && i >= get_long(&phil->table_info->mutex_meal_count, &phil->table_info->limit_eat))
            set_bool(&phil->mutex_meal_count, &phil->full, true);
    }
    else if (action == SLEEP)
    {
	    time = get_time_in_ms() - phil->table_info->time;
        printf(MAGENTA"%ld      %d is sleeping\n"RESET, time,  phil->index);// 😴
    }
    else if (action == THINK)
    {
	    time = get_time_in_ms() - phil->table_info->time;
        printf(CYAN"%ld      %d is thinking\n"RESET, time,  phil->index);// 🤔
    }
    my_mutex_function(UNLOCK, mtx);
}
