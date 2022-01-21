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

int message(t_args *ph, char *str)
{
    t_args	    *a;

	a = (t_args *)ph;
	sem_wait(a->send_mes);
    ft_putnbr_fd(get_time() / 1000, 1);
    ft_putstr_fd(" ", 1);
    ft_putnbr_fd(a->id + 1, 1);
    ft_putstr_fd(str, 1);
    if (ft_strlen(str) != 6)
        sem_post(a->send_mes);
    return (0);
}

static int put_forks_and_sleep(t_args *ph)
{
	t_args *a;

	a = (t_args *)ph;
	if (a->id % 2 != 0)
	sem_post(a->forks);
	sem_post(a->forks);
	a->meals--;
	if (a->meals == 0)
	{
		pthread_join(a->die_check, NULL);
		return (1);
	}
	message(a, " is sleeping\n");
	usleep(a->sleep_time);
	message(a, " is thinking\n");
	if (a->n % 2 != 0)
		usleep(a->eat_time * 2 - a->sleep_time);
	return (0);
}

static void take_forks_and_eat(t_args *ph)
{
	t_args *a;

	a = (t_args *)ph;
	if (a->id % 2 == 0)
	sem_wait(a->forks);
	sem_wait(a->forks);
	a->last_meal = get_time();
	message(a, " has taken a fork\n");
	message(a, " is eating\n");
	usleep(a->eat_time);
}

void	*activities(t_args *ph)
{	
	t_args	*a;

	a = (t_args *)ph;
	message(a, " is thinking\n");
	a->last_meal = get_time();
	pthread_create(&a->die_check, NULL, &die_my_darling, a);
	if (a->n % 2 == 0)
		usleep((a->id % 2) * a->eat_time / 2);
	else
		usleep((a->id % 3) * a->eat_time);
	while (1)
	{
		take_forks_and_eat(a);
		if (put_forks_and_sleep(a) == 1)
			break;
	}
	return (NULL);
}
