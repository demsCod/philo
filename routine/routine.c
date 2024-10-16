#include "../philo.h"

int is_full(philo *philosophe);

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

	if (is_full(philosophe))
		exit(0);
    if (action == TAKE_FORK)
    {
		pthread_mutex_lock(&philosophe->table_info->mutex_printf);
		temp = get_time_in_ms() - time ;
        printf("%ld  %d  has taken a fork\n", temp,  philosophe->index);// 🍴
		pthread_mutex_unlock(&philosophe->table_info->mutex_printf);
    }
    if (action == EAT)
    {
		pthread_mutex_lock(&philosophe->table_info->mutex_printf);
		temp = get_time_in_ms() - time;
		philosophe->eat_counters++;
        printf("%ld %d  is eating {🍝 %d} \n", temp,  philosophe->index, philosophe->eat_counters);//  🍝
        philosophe->last_eat = temp;
		pthread_mutex_unlock(&philosophe->table_info->mutex_printf);
        ft_usleep(philosophe->table_info->time_to_eat);
    }
    if (action == SLEEP)
    {
		pthread_mutex_lock(&philosophe->table_info->mutex_printf);
		temp = get_time_in_ms() - time ;
        printf("%ld %d is sleeping\n", temp,  philosophe->index);// 😴
		pthread_mutex_unlock(&philosophe->table_info->mutex_printf);
        ft_usleep(philosophe->table_info->time_to_sleep);
    }
    if (action == THINK)
    {
		pthread_mutex_lock(&philosophe->table_info->mutex_printf);
		temp = get_time_in_ms() - time ;
        printf("%ld %d is thinking\n", temp,  philosophe->index);// 🤔
		pthread_mutex_unlock(&philosophe->table_info->mutex_printf);
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
        ft_usleep(3e4);
    }
    else
    {
        philo_action(phi, THINK, temp);
    }
}
int is_philo_die(philo *philosophe)
{
	int die;

    pthread_mutex_lock(&philosophe->table_info->mutex_checking);
	die = philosophe->died;
    pthread_mutex_unlock(&philosophe->table_info->mutex_checking);

	return (die);
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


void *begin_routine(void *phi)
{
    philo *philosophe;
    time_t temp;

	philosophe = (philo *)phi;
	pthread_mutex_lock(&philosophe->table_info->mutex_printf);
	pthread_mutex_unlock(&philosophe->table_info->mutex_printf);
    temp = philosophe->table_info->time;
    //de_synchronize_philo(philosophe, temp);
    while (1)
    {
        if (is_end(philosophe))
            exit(0);
        if (is_philo_die(philosophe))
            exit(0);
		if (is_full(philosophe))
			exit(0);
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

void *check_monitor(t_table *table)
{
    philo  *philo_list;
    t_mtx   *mutex;

    pthread_mutex_lock(&table->mutex_printf);
	pthread_mutex_unlock(&table->mutex_printf);
    mutex = &table->mutex_checking;
    philo_list = table->philo;
    while (1)
    {
        pthread_mutex_lock(mutex);
        if (is_died(philo_list, mutex, table))
        {
            printf("%ld %i is died\n", get_time_in_ms() - table->time, philo_list->index);
            exit (0);
        }
        philo_list = philo_list->next;
        pthread_mutex_unlock(mutex);
		ft_usleep(10);

    }
}
int routine_philo (philo **philo_list)
{
    pthread_t *thread_for_phil;
    // pthread_t monitor;

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
	pthread_mutex_init(&table->mutex_checking, NULL);
	pthread_mutex_init(&table->mutex_printf, NULL);
	pthread_mutex_lock(&table->mutex_printf);
    while (number_philo > 0)
    {
		philo->fork = malloc(sizeof(t_mtx));
    	pthread_mutex_init(philo->fork, NULL);
        pthread_create(&thread_for_phil[i], NULL, begin_routine, philo);
        philo = philo->next;
        number_philo--;
        i++;
    }
    j = 0;
	table->time = get_time_in_ms();
	pthread_mutex_unlock(&table->mutex_printf);
	check_monitor(table);
    while (j < i)
    {
        pthread_join(thread_for_phil[j], NULL);
        j++;
    }
	return (0);
}