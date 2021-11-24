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

    int             sec;
    int             usec;

	pthread_mutex_t	mutex;
}					t_philo;

int					ft_atoi(char const *str);

#endif