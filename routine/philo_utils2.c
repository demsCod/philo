#include "../philo.h"

void philo_print(t_mtx *mtx, philo *phil, int action)
{
    time_t time;

    if (get_bool(&phil->table_info->mutex_checking,  &phil->died) || get_bool(&phil->table_info->mutex_checking,  &phil->table_info->end))
            return;
    my_mutex_function(LOCK, mtx);
    if (action ==  TAKE_FORK)
    {
	    time = get_time_in_ms() - phil->table_info->time;
        printf("%ld      %d has taken a fork 🍴\n", time,  phil->index);// 🍴
    }
    else if (action ==  EAT)
    {
	    time = get_time_in_ms() - phil->table_info->time;
        printf("%ld      %d is eating {🍝 %d} \n", time,  phil->index, phil->eat_counters);//  🍝
    }
    else if (action == SLEEP)
    {
	    time = get_time_in_ms() - phil->table_info->time;
        printf("%ld      %d is sleeping 😴\n", time,  phil->index);// 😴
    }
    else if (action == THINK)
    {
	    time = get_time_in_ms() - phil->table_info->time;
        printf("%ld      %d is thinking 🤔\n", time,  phil->index);// 🤔
    }
    my_mutex_function(UNLOCK, mtx);
}
