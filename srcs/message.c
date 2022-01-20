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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int message(t_philo *ph, char *str)
{
    t_philo	    *a;
    int         i;

	a = (t_philo *)ph;
    i = 0;
    while (a->ar->send_mes == 0)
    {
        usleep(10);
        if (a->dead == 1)
            return (1);
        if (i++ > 100)
            return (1);
    }
    a->ar->send_mes = 0;
    ft_putnbr_fd(get_time() / 1000, 1);
    ft_putstr_fd(" ", 1);
    ft_putnbr_fd(a->id + 1, 1);
    ft_putstr_fd(str, 1);
    if (ft_strlen(str) != 6)
        a->ar->send_mes = 1;
    return (0);
}