#include "../include/philo.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
    int     j;

	i = 0;
    j = 0;
	while (s[i])
		j = j + write (fd, &s[i++], 1);
    return (i);
}

void message(long int ms, int n, char *str, pthread_mutex_t *send_mes)
{
    pthread_mutex_lock(send_mes);
    ft_putnbr_fd(ms, 1);
    ft_putstr_fd(" ", 1);
    ft_putnbr_fd(n, 1);
    ft_putstr_fd(str, 1);
    pthread_mutex_unlock(send_mes);
}