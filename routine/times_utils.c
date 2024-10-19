#include "../philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval		tv;

	if (gettimeofday(&tv, NULL))
    {
        ft_putendl_fd("gettime failed\n", 2);
        exit(123);
    }
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < milliseconds)
		usleep(0.1);
	return (0);
}