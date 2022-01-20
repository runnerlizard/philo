#include "../include/philo_bonus.h"

long int get_time()
{
	static struct timeval	tv1;
	struct timeval			tv2;
	static struct timezone	tz;
	static int				i;
	
	if (i == 0)
	{
		i = 1;
		gettimeofday(&tv1, &tz);
	}
	else
	{
		gettimeofday(&tv2, &tz);
		return ((tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec);
	}
	return (0);
}
/*
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

static int put_forks_and_sleep(t_philo *ph)
{
	t_philo *a;

	a = (t_philo *)ph;
	if (a->id % 2 != 0)
	{
		pthread_mutex_unlock(&a->ar->forks[a->r]);
		pthread_mutex_unlock(&a->ar->forks[a->id]);
	}
	else
	{
		pthread_mutex_unlock(&a->ar->forks[a->id]);
		pthread_mutex_unlock(&a->ar->forks[a->r]);
	}
	a->meals--;
	if (a->meals == 0)
	{
		pthread_join(a->die_check, NULL);
		return (1);
	}
	message(a, " is sleeping\n");
	usleep(a->ar->sleep_time);
	message(a, " is thinking\n");
	if (a->ar->n % 2 != 0)
		usleep(a->ar->eat_time * 2 - a->ar->sleep_time);
	return (0);
}

static void take_forks_and_eat(t_philo *ph)
{
	t_philo *a;

	a = (t_philo *)ph;
	if (a->id % 2 == 0)
	{
		pthread_mutex_lock(&a->ar->forks[a->id]);
		pthread_mutex_lock(&a->ar->forks[a->r]);
	}
	else
	{
		pthread_mutex_lock(&a->ar->forks[a->r]);
		pthread_mutex_lock(&a->ar->forks[a->id]);
	}
	a->last_meal = get_time();
	message(a, " has taken a fork\n");
	message(a, " is eating\n");
	usleep(a->ar->eat_time);
}

void	*activities(void *ph)
{	
	t_philo	*a;

	a = (t_philo *)ph;
	message(a, " is thinking\n");
	a->last_meal = get_time();
	pthread_create(&a->die_check, NULL, &die_my_darling, a);
	if (a->ar->n % 2 == 0)
		usleep((a->id % 2) * a->ar->eat_time / 2);
	else
		usleep((a->id % 3) * a->ar->eat_time);
	while (a->dead == 0)
	{
		take_forks_and_eat(a);
		if (put_forks_and_sleep(a) == 1)
			break;
	}
	pthread_join(a->die_check, NULL);
	return (NULL);
}*/
