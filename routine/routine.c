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

void *begin_routine(void *phi)
{
    philo *philosophe;
    struct timeval *time;
	void 			*rest;
    time_t res;
    time_t temp;
    pthread_mutex_t mutex;

    temp = get_time_in_ms();
    philosophe = (philo*)phi;
    philosophe->fork = malloc(sizeof(t_mtx));
    pthread_mutex_init(&mutex, NULL);
    while (1)
    {
        pthread_mutex_lock(philosophe->table_info->mutex);
        if (philosophe->table_info->thread_ready)
        {
             pthread_mutex_unlock(philosophe->table_info->mutex);
             break;
        }
        pthread_mutex_unlock(philosophe->table_info->mutex);
    }
    while (1)
    {
        res = get_time_in_ms() - temp;
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
    while (number_philo > 0)
    {
        pthread_create(&thread_for_phil[i], NULL, begin_routine, philo);
        philo = philo->next;
        number_philo--;
        i++;
    }
    ft_usleep(500);
    pthread_mutex_lock(table->mutex);
    table->thread_ready = true;
    pthread_mutex_unlock(table->mutex);
    j = 0;
    while (j < i)
    {
        pthread_join(thread_for_phil[j], NULL);
        j++;
    }
}