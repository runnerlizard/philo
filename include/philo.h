#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_args
{
    int             n;
	int             die_time;
	int             eat_time;
    int             sleep_time;
    int             number;
    int             send_mes;
    pthread_mutex_t	*forks; // destroyed freed
}					t_args;

typedef struct		s_philo
{
    int             id;
    int             r;
    int             dead;
    int             meals;
    int             last_meal;
    pthread_t       t;  //joined
    pthread_t       die_check; //joined
    t_args          *ar;
}					t_philo;

int         ft_atoi(char const *str);
int         message(t_philo *ph, char *str);
int 	    ft_putstr_fd(char *s, int fd);
void	    ft_putnbr_fd(long int n, int fd);
size_t      ft_strlen(const char *str);
long int    get_time();

#endif