#include "../philo.h"

void my_mutex_function(int FLAG, t_mtx *mtx)
{
    if (FLAG == LOCK)
    {
       if (pthread_mutex_lock(mtx) == -1)
            ft_putendl_fd("fail to lock the mutex", 2);
    }
    else if (FLAG == UNLOCK)
    {
       if (pthread_mutex_unlock(mtx) == -1)
            ft_putendl_fd("fail to unlock the mutex", 2);
    }
    else if (FLAG == INIT)
    {
         if (pthread_mutex_init(mtx, NULL) == -1)
            ft_putendl_fd("fail to init the mutex", 2);
    }
    else if (FLAG == DESTROY)
    {
         if (pthread_mutex_destroy(mtx) == -1)
            ft_putendl_fd("fail to destroy the mutex", 2);
    }
    else 
        ft_putendl_fd("Error no good flag dor mutex !!!!", 2);
}

bool get_bool(t_mtx *mtx, bool value)
{
    bool ret;

    my_mutex_function(LOCK, mtx);
    ret = value;
    my_mutex_function(UNLOCK, mtx);
    return (ret);
}

long get_long(t_mtx *mtx, long *value)
{
    long ret;

    my_mutex_function(LOCK, mtx);
    ret = *value;
    my_mutex_function(UNLOCK, mtx);
    return (ret);
}
void set_bool(t_mtx *mtx, bool *dest, bool src)
{
    my_mutex_function(LOCK, mtx);
    *dest = src;
    my_mutex_function(UNLOCK, mtx);
    return ;
}

void set_long(t_mtx *mtx, long *dest, long src)
{
    my_mutex_function(LOCK, mtx);
    *dest = src;
    my_mutex_function(UNLOCK, mtx);
    return ;
}