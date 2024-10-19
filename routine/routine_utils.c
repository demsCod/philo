
#include "../philo.h"


bool is_died(philo *phil, t_mtx  *mtx)
{
    return(get_bool(mtx, &phil->died));
}


void de_synchronize_philo(philo *phi)
{
    if (phi->index % 2 == 0)
            ft_usleep(10);
}

bool is_philo_die(philo *philosophe)
{
	time_t last_eat;

	
    last_eat = (get_time_in_ms() - philosophe->table_info->time) - get_long(&philosophe->mutex_meal_time, &philosophe->last_eat);
    if (last_eat > philosophe->table_info->time_to_die)
        return (true);
    return (false);
}

int is_end(philo *philosophe)
{
	int end;

    pthread_mutex_lock(&philosophe->table_info->mutex_checking);
	end = philosophe->table_info->end;
    pthread_mutex_unlock(&philosophe->table_info->mutex_checking);

	return (end);
}

int is_full(philo *philosophe)
{
	int count;

    pthread_mutex_lock(&philosophe->table_info->mutex_checking);
	if (philosophe->table_info->extra_args == false)
	{
		count = 0;
		pthread_mutex_unlock(&philosophe->table_info->mutex_checking);
		return (count);
	}
	count = 0;
	if (philosophe->eat_counters >= philosophe->table_info->limit_eat)
		count = 1;
    pthread_mutex_unlock(&philosophe->table_info->mutex_checking);
	return (count);
}