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

void philo_action (philo *philosophe, int action, long time)
{

	time_t temp;

    if (action == TAKE_FORK)
    {
		pthread_mutex_lock(philosophe->table_info->mutex_printf);
		temp = get_time_in_ms() - time ;
        printf("%ld  %d  has taken a fork\n", temp,  philosophe->index);// 🍴
		pthread_mutex_unlock(philosophe->table_info->mutex_printf);
    }
    if (action == EAT)
    {
		pthread_mutex_lock(philosophe->table_info->mutex_printf);
		temp = get_time_in_ms() - time;
        printf("%ld %d  is eating\n", temp,  philosophe->index);//  🍝
        philosophe->last_eat = temp;
		pthread_mutex_unlock(philosophe->table_info->mutex_printf);
        ft_usleep(philosophe->table_info->time_to_eat);
    }
    if (action == SLEEP)
    {
		pthread_mutex_lock(philosophe->table_info->mutex_printf);
		temp = get_time_in_ms() - time ;
        printf("%ld %d is sleeping\n", temp,  philosophe->index);// 😴
		pthread_mutex_unlock(philosophe->table_info->mutex_printf);
        ft_usleep(philosophe->table_info->time_to_sleep);
    }
    if (action == THINK)
    {
		pthread_mutex_lock(philosophe->table_info->mutex_printf);
		temp = get_time_in_ms() - time ;
        printf("%ld %d is thinking\n", temp,  philosophe->index);// 🤔
		pthread_mutex_unlock(philosophe->table_info->mutex_printf);
        ft_usleep(philosophe->table_info->time_to_think);

    }
}

void take_fork(philo *phil, t_mtx *mtx, time_t temp)
{
	pthread_mutex_lock(mtx);
    philo_action(phil, TAKE_FORK, temp);
}

void de_synchronize_philo(philo *phi, time_t temp)
{
    if (phi->index % 2 == 0)
    {
        ft_usleep(100);
    }
    else
    {
        philo_action(phi, THINK, temp);
    }
}
void *begin_routine(void *phi)
{
    philo *philosophe;
    time_t temp;

	philosophe = (philo *)phi;
	pthread_mutex_lock(philosophe->table_info->mutex_printf);
	pthread_mutex_unlock(philosophe->table_info->mutex_printf);
    temp = philosophe->table_info->time;
    de_synchronize_philo(philosophe, temp);
    while (1)
    {
        pthread_mutex_lock(philosophe->table_info->mutex_printf);
        if (philosophe->table_info->end)
            exit(0);
        if (philosophe->died)
        {
            printf("%ld %d is died  [ %ld ]\n", (get_time_in_ms() - temp), philosophe->index, philosophe->last_eat);
            exit(0);
        }
        pthread_mutex_unlock(philosophe->table_info->mutex_printf);
        if (philosophe->index % 2 == 0)
        {
            take_fork(philosophe, philosophe->fork, temp);
            take_fork(philosophe, philosophe->next->fork, temp);
            philo_action(philosophe, EAT, temp);
			pthread_mutex_unlock(philosophe->fork);
			pthread_mutex_unlock(philosophe->next->fork);
        }
        else
        {   
            take_fork(philosophe, philosophe->next->fork, temp);
            take_fork(philosophe, philosophe->fork, temp);
            philo_action(philosophe, EAT, temp);
			pthread_mutex_unlock(philosophe->next->fork);
			pthread_mutex_unlock(philosophe->fork);
        }
        philo_action(philosophe, SLEEP, temp);
        philo_action(philosophe, THINK, temp);
    }
}

bool is_died(philo *phil, t_mtx  *mtx, t_table *table)
{

    time_t time;

    time = get_time_in_ms() - table->time;
    if (time - phil->last_eat > table->time_to_die)
    {
        // printf("[%ld - %ld]\n", time, phil->last_eat);
        phil->died = true;
        table->end = true;
        pthread_mutex_unlock(mtx);
        return (true);
    }
    return (false);

}
// add lock unlock before runnig threqd qnd printf 

void *check_monitor(void *table_data)
{
    t_table *table;
    philo  *philo_list;
    t_mtx   *mutex;

    table = (t_table *)table_data;
    pthread_mutex_lock(table->mutex_printf);
	pthread_mutex_unlock(table->mutex_printf);

    mutex = malloc(sizeof(t_mtx));
    pthread_mutex_init(mutex, NULL);
    table = (t_table *)table_data;
    philo_list = table->philo;
    while (1)
    {
        pthread_mutex_lock(mutex);

        if (is_died(philo_list, mutex, table))
        {
            printf("%ld %i is died [%ld]\n", get_time_in_ms() - table->time, philo_list->index, (get_time_in_ms() - table->time) - philo_list->last_eat);
            exit (0);
        }
        philo_list = philo_list->next;
        pthread_mutex_unlock(mutex);

    }
}
int routine_philo (philo **philo_list)
{
    pthread_t *thread_for_phil;
    pthread_t monitor;

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
	table->mutex_printf = malloc(sizeof(t_mtx));
	pthread_mutex_init(table->mutex_printf, NULL);
	pthread_mutex_lock(table->mutex_printf);
    while (number_philo > 0)
    {
		philo->fork = malloc(sizeof(t_mtx));
    	pthread_mutex_init(philo->fork, NULL);
        pthread_create(&thread_for_phil[i], NULL, begin_routine, philo);
        philo = philo->next;
        number_philo--;
        i++;
    }
    pthread_create(&monitor, NULL, check_monitor,  table);
    j = 0;
	table->time = get_time_in_ms();
	pthread_mutex_unlock(table->mutex_printf);
    while (j < i)
    {
        pthread_join(thread_for_phil[j], NULL);
        j++;
    }
    pthread_join(monitor, NULL);
	return (0);
}