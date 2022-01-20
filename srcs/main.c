#include "../include/philo.h"


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

static void *die_my_darling(void *ph)
{
	t_philo	*a;

	a = (t_philo *)ph;
	while (1)
	{
		if (a->ar->die_time < get_time() - a->last_meal)
		{
			message(a, " died\n");
			a->dead = 1;
			pthread_mutex_unlock(&a->ar->forks[a->r]);
			pthread_mutex_unlock(&a->ar->forks[a->id]);
			return (0);
		}
		if (a->meals == 0)
			return (0);
		usleep(5);
	}
	return(NULL);
}

static void	*routine(void *ph)
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
			return (0);
		}
		message(a, " is sleeping\n");
		usleep(a->ar->sleep_time);
		message(a, " is thinking\n");
		if (a->ar->n % 2 != 0)
			usleep(a->ar->eat_time * 2 - a->ar->sleep_time);
	}
	pthread_join(a->die_check, NULL);
	return (NULL);
}

static int check_create_args(int argc, char **argv, t_args *a)
{	
	int	i;

	if ((argc != 6) && (argc != 5))
		return (ft_putstr_fd("Invalid arguments number. Must be 5 or 4\n", 1));
	a->n = ft_atoi(argv[1]);
	a->die_time = ft_atoi(argv[2]) * 1000;
	a->eat_time = ft_atoi(argv[3]) * 1000;
	a->sleep_time = ft_atoi(argv[4]) * 1000;
	a->number = -1;
	if (argc == 6)
		a->number = ft_atoi(argv[5]);
	if ((a->n < 1) || (a->die_time < 0) || (a->eat_time < 0) || (a->sleep_time < 0) || ( (argc == 6) && (a->number < 0)))
		return (ft_putstr_fd("Invalid arguments.\n", 1));
	a->send_mes = 1;
	i = 0;
	a->forks = malloc(sizeof(pthread_mutex_t) * a->n);
	if (a->forks == NULL)
		return (ft_putstr_fd("Malloc error\n", 1));
	while (i < a->n)
		pthread_mutex_init(&a->forks[i++], NULL);
	get_time();
	return (0);
}

int main (int argc, char *argv[])
{
	t_args	*a;
	t_philo	*p;
	int		i;
	
	a = malloc(sizeof(t_args));
	if (a == NULL)
		return (1);
	if (check_create_args(argc, argv, a) != 0)
		return (1);
	if (!(p = malloc(sizeof(t_philo) * a->n)))
		return (ft_putstr_fd("Malloc error1\n", 1));
	i = 0;
	while (i < a->n)
	{
		p[i].id = i;
		if (i == a->n - 1)
			p[i].r = 0;
		else
			p[i].r = i + 1;
		p[i].dead = 0;
		p[i].meals = a->number;
		p[i].ar = a;
		if (pthread_create(&p[i].t, NULL, &routine, &p[i]) != 0)
			return (ft_putstr_fd("pthread_create error!\n", 1));
		i++;
	}
	while (--i >= 0)
	{
		pthread_join(p[i].t, NULL);
		pthread_mutex_destroy(&a->forks[i]);
	}
	free(a->forks);
	free(a);
	free(p);
	return (argc);
}
