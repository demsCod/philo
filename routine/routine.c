#include "../philo.h"

void wait_is_ready(t_mtx *mtx, bool *ready)
{
	while(get_bool(mtx, ready) == false)
		;
}

void *begin_routine(void *phi)
{
    philo *philosophe;
 
	philosophe = (philo *)phi;
	wait_is_ready(&philosophe->table_info->mutex_ready, &philosophe->table_info->ready);
    set_long(&philosophe->mutex_meal_time ,&philosophe->last_eat, 0);
    de_synchronize_philo(philosophe);
    while (1)
    {
        if (get_bool(&philosophe->table_info->mutex_meal_count, &philosophe->full))
            break;
        if (get_bool(&philosophe->ph_mutex, &philosophe->died))
            break;
        if (get_bool(&philosophe->table_info->mutex_checking, &philosophe->table_info->end))
            break;
        if (philosophe->index % 2 == 0)
        {
            take_fork(philosophe, philosophe->fork);
            take_fork(philosophe, philosophe->next->fork);
            philo_action(philosophe, EAT);
			my_mutex_function(UNLOCK, philosophe->fork);
			my_mutex_function(UNLOCK, philosophe->next->fork);
        }
        else
        {   
            take_fork(philosophe, philosophe->next->fork);
            take_fork(philosophe, philosophe->fork);
            philo_action(philosophe, EAT);
			my_mutex_function(UNLOCK, philosophe->next->fork);
			my_mutex_function(UNLOCK, philosophe->fork);
        }
        philo_action(philosophe, SLEEP);
        philo_action(philosophe, THINK);
    }
    return NULL;
}

void *check_monitor(t_table *table)
{
    philo  *philo_list;

    wait_is_ready(&table->mutex_ready, &table->ready);
    philo_list = table->philo;
    while (1)
    {
        if (get_bool(&table->mutex_meal_count, &philo_list->full))
		{
            my_mutex_function(LOCK, &table->mutex_ready);
            philo_list = philo_list->next;
		    my_mutex_function(UNLOCK, &table->mutex_ready);
        }
        else
        {
            if (is_philo_die(philo_list))
            {
                set_bool(&philo_list->ph_mutex, &philo_list->died , true);
                set_bool(&table->mutex_checking, &table->end , true);
                my_mutex_function(LOCK, &table->mutex_printf);
                printf("%ld      %i is died 💀\n", get_time_in_ms() - table->time, philo_list->index);
                my_mutex_function(UNLOCK, &table->mutex_printf);
                return NULL;
            }
            my_mutex_function(LOCK, &table->mutex_ready);
            philo_list = philo_list->next;
            my_mutex_function(UNLOCK, &table->mutex_ready);
        }
    }
}

int routine_philo (philo **philo_list)
{
    pthread_t *thread_for_phil;
    philo *philo;
    t_table *table;
    int number_philo;
    int i;
    int j;

    i = 0;
    philo = *philo_list;
    table = philo->table_info;
    number_philo = philo->number_of_philo;
    thread_for_phil = malloc(sizeof(pthread_t) * number_philo);
    table->philo = philo;
	my_mutex_function(INIT, &table->mutex_checking);
	my_mutex_function(INIT, &table->mutex_printf);
	my_mutex_function(INIT, &table->mutex_meal_count);
    
	my_mutex_function(INIT, &table->mutex_calcul_think_time);
	my_mutex_function(INIT, &table->mutex_dead);
	my_mutex_function(INIT, &table->mutex_ready);
    while (number_philo > 0)
    {
		philo->fork = malloc(sizeof(t_mtx));
    	pthread_mutex_init(philo->fork, NULL);
	    my_mutex_function(INIT, &philo->mutex_meal_time);
	    my_mutex_function(INIT, &philo->ph_mutex);
	    my_mutex_function(INIT, &philo->mutex_meal_count);


        pthread_create(&thread_for_phil[i], NULL, begin_routine, philo);
        philo = philo->next;
        number_philo--;
        i++;
    }
    j = 0;
	table->time = get_time_in_ms();
	set_bool(&table->mutex_ready, &table->ready, true);
	check_monitor(table);
    while (j < i)
    {
        pthread_join(thread_for_phil[j], NULL);
        j++;
    }
	return (0);
}
