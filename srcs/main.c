#include "../include/philo.h"


static long int get_time()
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

static void *die_die_die_my_darling(void *ph)
{
	t_p	*b;

	b = (t_p *)ph;
	while (1)
	{
		if (b->a->die_time < get_time() - b->a->p[b->id].last_meal)
		{
			pthread_mutex_unlock(&b->a->meal_or_die[b->id]);
			message(get_time(), b->id + 1, " died\n", &b->a->send_mes);
		}
		usleep(5);
	}
	return(NULL);
}

static void ft_usleep(int us)
{
	unsigned int	timer;

	timer = get_time();
	while (get_time() - timer < us)
		usleep(10);
}

static void	*routine(void *a)
{	
	t_p	ph;

	ph.a = (t_args *)a;
	ph.id = ph.a->tmp_id;
	ph.meals = ph.a->number;
	if (ph.id == ph.a->n - 1)
		ph.r = 0;
	else
		ph.r = ph.id + 1;


	



	ph.a->p[ph.id].last_meal = get_time();
	pthread_create(&ph.a->p[ph.id].die_check, NULL, &die_die_die_my_darling, &ph);
	while (1)
	{
		message(get_time(), ph.id + 1, " is thinking\n", &ph.a->send_mes);
		if (ph.a->n % 2 != 0)
			ft_usleep(ph.a->eat_time * 2 - ph.a->sleep_time);
		if (ph.id % 2 == 0)
		{
			pthread_mutex_lock(&ph.a->p[ph.r].fork);
			pthread_mutex_lock(&ph.a->p[ph.id].fork);
		}
		else
		{
			pthread_mutex_lock(&ph.a->p[ph.id].fork);
			pthread_mutex_lock(&ph.a->p[ph.r].fork);
		}
		ph.a->p[ph.id].last_meal = get_time();
		message(get_time(), ph.id + 1, " has taken a fork\n", &ph.a->send_mes);
		message(get_time(), ph.id + 1, " is eating\n", &ph.a->send_mes);
		ph.meals--;
		if (ph.meals == 0)
			pthread_mutex_unlock(&ph.a->meal_or_die[b->id]);
		ft_usleep(ph.a->eat_time);
		if (ph.id % 2 != 0)
		{
			pthread_mutex_unlock(&ph.a->p[ph.r].fork);
			pthread_mutex_unlock(&ph.a->p[ph.id].fork);
		}
		else
		{
			pthread_mutex_unlock(&ph.a->p[ph.id].fork);
			pthread_mutex_unlock(&ph.a->p[ph.r].fork);
		}
		message(get_time(), ph.id + 1, " is sleeping\n", &ph.a->send_mes);
		ft_usleep(ph.a->sleep_time);
	}
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
	pthread_mutex_init(&a->send_mes, NULL);
	if (!(a->p = malloc(sizeof(t_philo) * a->n)))
		return (ft_putstr_fd("Malloc error1\n", 1));
	if (!(a->meal_or_die = malloc(sizeof(pthread_mutex_t) * a->n)))
		return (ft_putstr_fd("Malloc error2\n", 1));
	i = 0;
	while (i < a->n)
	{
		pthread_mutex_init(&a->meal_or_die[i], NULL);
		pthread_mutex_init(&a->p[i++].fork, NULL);
	}
	get_time();
	return (0);
}

static void	*finisher(void *a)
{
	int	i;
	t_p	ph;

	ph.a = (t_args *)a;
	i = 0;
	while (i < ph.n)
		pthread_mutex_lock(&ph.a->die_or_meal[i++]);
		i = 0;
	while (i < ph.n)
		pthread_mutex_lock(&ph.a->die_or_meal[i++]);
	//destroy all, join all, free all
}

int main (int argc, char *argv[])
{
	t_args	a;
	int		i;
	
	if (check_create_args(argc, argv, &a) != 0)
		return (1);
	if (pthread_create(&a.finish, NULL, &finisher, &a) != 0)
		return (printf("pthread_create error!\n"));
	i = 1;
	while (i < a.n)
	{
		a.tmp_id = i;
		if (pthread_create(&a.p[i].t, NULL, &routine, &a) != 0)
			return (printf("pthread_create error!\n"));
		ft_usleep(500);
		i += 2;
		if (((i == a.n + 1) || (i == a.n)) && (i % 2 == 1))
			i = 0;
	}
	usleep(100000000);
	return (argc);
}
	/*	while (j-- > 0)
	{
		printf("joined %d\n", i[0] - j);
		if (pthread_join(t[j], NULL) != 0)
			return (printf("pthread_join error!\n"));
		usleep(10);
	}*/

