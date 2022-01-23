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
	ft_putnbr_fd(a->id, 1);
	ft_putstr_fd(str, 1);
	sem_wait(a->send_mes);
	if ((get_time() - a->last_mes > a->die_time))
	{
		ft_putstr_fd("here\n", 1);
		ft_putnbr_fd(a->id, 1);
		a->dead = 1;
		return (1);
	}
    ft_putnbr_fd(get_time() / 1000, 1);
    ft_putstr_fd(" ", 1);
    ft_putnbr_fd(a->id + 1, 1);
    ft_putstr_fd(str, 1);
	a->last_mes = get_time();
    if (ft_strlen(str) != 6)
        sem_post(a->send_mes);
	else
		a->dead = 1;
    return (0);
}

static int put_forks_and_sleep(t_args *ph)
{
	t_args *a;

	a = (t_args *)ph;
	usleep(a->eat_time);
	if (a->dead == 1)
		return (1);
	sem_post(a->forks);
	sem_post(a->forks);
	a->meals--;
	if ((a->meals == 0) || (a->dead == 1))
		return (1);
	message(a, " is sleeping\n");
	usleep(a->sleep_time);
	if (a->dead == 1)
		return (1);
	message(a, " is thinking\n");
	if (a->n % 2 != 0)
		usleep(a->eat_time * 2 - a->sleep_time);
	if (a->dead == 1)
		return (1);
	return (0);
}

static int take_forks_and_eat(t_args *ph)
{
	t_args *a;

	a = (t_args *)ph;
	if (a->dead == 1)
		return (1);
	sem_wait(a->forks);
	if (a->dead == 1)
		return (1);
	sem_wait(a->forks);
	if (a->dead == 1)
		return (1);
	a->last_meal = get_time();
	message(a, " has taken a fork\n");
	message(a, " is eating\n");
	sem_post(a->forks);
	sem_post(a->forks);
	return (0);
}

void	*activities(t_args *ph)
{	
	t_args	*a;

	a = (t_args *)ph;
	message(a, " is thinking\n");
	a->last_meal = get_time();
	pthread_create(&a->die_check, NULL, &die_my_darling, a);
	if (a->id >= a->n / 2)
		usleep(a->eat_time / 2);
	if (a->n % 2 != 0)
		usleep(a->eat_time * (a->id % 3));
	while (1)
	{
		if ((take_forks_and_eat(a) == 1) || (put_forks_and_sleep(a) == 1))
		{
			sem_close(a->send_mes);
			sem_close(a->forks);
			free(a->pid);
			free(a);
			break;
		}
	}
	ft_putnbr_fd(a->id, 1);
	ft_putstr_fd("finish\n", 1);
	pthread_join(a->die_check, NULL);
	return (NULL);
}
