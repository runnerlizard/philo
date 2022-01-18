#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_philo
{
    pthread_mutex_t	fork;
    pthread_t       t;
    int             last_meal;
    pthread_t       second_fork;
    int             left;
    int             right;
}					t_philo;

typedef struct		s_args
{
    int             n;
    int             tmp_id;
	int             die_time;
	int             eat_time;
    int             sleep_time;
    int             number;
    pthread_mutex_t send_mes;
    t_philo         *p;
}					t_args;

typedef struct		s_p
{
    int             id;
    int             r;
    t_args          *a;
}					t_p;

int     ft_atoi(char const *str);
void    message(long int ms, int n, char *str, pthread_mutex_t *send_mes);
int 	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(long int n, int fd);

#endif