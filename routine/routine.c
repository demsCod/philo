#include "../philo.h"

void *begin_routine(void *phi)
{
    philo *philosophe;

    philosophe = (philo*)phi;
    while (1)
    {
        if (philosophe->fork && philosophe->next->fork)
        {
            // mutex to change value of fork and husband fork
            // eat; 
        }
        // if (philo->end_eat)
        //     // sleep
        // think
    }
    
}
int routine_philo (philo **philo_list)
{
    pthread_t *thread_for_phil;
    int number_philo;
    int i;
    philo *philo;

    i = 0;
    philo = *philo_list;
    number_philo = (*philo_list)->number_of_philo;
    thread_for_phil = malloc(sizeof(thread_for_phil) * number_philo);
    while (number_philo > 0)
    {
        pthread_create(&thread_for_phil[i], NULL, begin_routine, philo);
        philo = philo->next;
        i++;
        number_philo--;
    }
    
}