#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_philo
{
    int             n;
	int             die_time;
	int             eat_time;
    int             sleep_time;
    int             number;
    int             p_num;
    int             *last_meal;
    pthread_mutex_t	*fork;
    pthread_mutex_t send_mes;
}					t_philo;

int     ft_atoi(char const *str);
void    message(long int ms, int n, char *str, pthread_mutex_t *send_mes);
int 	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(long int n, int fd);

#endif