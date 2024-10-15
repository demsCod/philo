#include "../philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < milliseconds)
		usleep(500);
	return (0);
}

void philo_action (philo *philosophe, int action, int time)
{

    if (action == TAKE_FORK)
    {
        printf("%d  %d  has taken fork 🍴\n", time, philosophe->index);
    }
    if (action == EAT)
    {
        printf("%d %d  is eating 🍝\n", time, philosophe->index);
        philosophe->last_eat = time;
        ft_usleep(philosophe->table_info->time_to_eat);
    }
    if (action == SLEEP)
    {
        printf("%d %d is sleeping 😴\n", time, philosophe->index);
        ft_usleep(philosophe->table_info->time_to_sleep);
    }
    if (action == THINK)
    {
        printf("%d %d is thinking 🤔\n", time, philosophe->index);
        ft_usleep(philosophe->table_info->time_to_think);
    }
}

void take_fork(philo *phil, t_mtx *mtx, time_t temp)
{
    int time;

    time = get_time_in_ms() - temp;
    pthread_mutex_lock(mtx);
    philo_action(phil, TAKE_FORK, time);
}

void wait_thread(t_table *table)
{
    while (1)
    {
        pthread_mutex_lock(table->mutex);
        if (table->thread_ready == true)
        {
             pthread_mutex_unlock(table->mutex);
             break;
        }
        pthread_mutex_unlock(table->mutex);
    }
}

void *begin_routine(void *phi)
{
    philo *philosophe;
    struct timeval *time;
	void 			*rest;
    time_t res;
    time_t temp;
    t_mtx  lock_time;


    pthread_mutex_init(&lock_time, NULL);

    temp = get_time_in_ms();
    philosophe = (philo*)phi;
    pthread_mutex_lock(&lock_time);
    philosophe->table_info->time = 0;
    pthread_mutex_unlock(&lock_time);
    philosophe->fork = malloc(sizeof(t_mtx));
    pthread_mutex_init(philosophe->fork, NULL);
    wait_thread(philosophe->table_info);
    while (1)
    {
        res = get_time_in_ms() - temp;
        pthread_mutex_lock(philosophe->table_info->mutex);
        philosophe->table_info->time = res;
        pthread_mutex_unlock(philosophe->table_info->mutex);

        if (philosophe->index % 2 == 0)
        {
            take_fork(philosophe, philosophe->fork, temp);
            take_fork(philosophe, philosophe->next->fork, temp);
            philo_action(philosophe, EAT, res);
            pthread_mutex_unlock(philosophe->fork);
            pthread_mutex_unlock(philosophe->next->fork);
        }
        else
        {   
            take_fork(philosophe, philosophe->next->fork, temp);
            take_fork(philosophe, philosophe->fork, temp);
            philo_action(philosophe, EAT, res);
            pthread_mutex_unlock(philosophe->next->fork);
            pthread_mutex_unlock(philosophe->fork);
        }
        res = get_time_in_ms() - temp;
        philo_action(philosophe, SLEEP, res);
        res = get_time_in_ms() - temp;
        philo_action(philosophe, THINK, res);
    }
}

bool is_died(philo *phil, t_mtx  *mtx, t_table *table)
{

    time_t time;

    time = get_time_in_ms() ;
    //printf("%d\n", table->time);
    pthread_mutex_lock(mtx);
    if (time - phil->last_eat > table->time_to_die)
    {
        phil->died = true;
        pthread_mutex_unlock(mtx);
        return (true);
    }
    pthread_mutex_unlock(mtx);
    return (false);

}

void *check_monitor(void *table_data)
{
    t_table *table;
    philo  *philo_list;
    t_mtx   *mutex;

    mutex = malloc(sizeof(t_mtx));
    pthread_mutex_init(mutex, NULL);
    table = (t_table *)table_data;
    wait_thread(table);
    philo_list = table->philo;
    table->time =  0;
    while (1)
    {
        // if (is_died(philo_list, mutex, table))
        //     printf("A PHILO IS DIEDDDDDDD !!!!!!\n");
        philo_list = philo_list->next;
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
    thread_for_phil = malloc(sizeof(pthread_t) * number_philo );
    table->philo = philo;
	pthread_mutex_init(table->mutex, NULL);
    while (number_philo > 0)
    {
        pthread_create(&thread_for_phil[i], NULL, begin_routine, philo);
        philo = philo->next;
        number_philo--;
        i++;
    }
    pthread_create(table->monitor, NULL, check_monitor,  table);
    ft_usleep(100);
    table->thread_ready = true;
    j = 0;
    while(1);
    while (j < i)
    {
        pthread_join(thread_for_phil[j], NULL);
        j++;
    }
}