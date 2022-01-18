#include "../include/philo.h"


int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	a;
	int		sign;

	i = 0;
	sign = 1;
	a = 0;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == ' '))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= 48) & (str[i] <= 57) & (a < 9999999999))
	{
		a = (a * 10) + (str[i] - 48);
		i++;
	}
	if ((a > 2147483648) && (sign == -1))
		return (0);
	if ((a > 2147483648) || ((a == 2147483648) && (sign == 1)))
		return (-1);
	return (a * sign);
}

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
		return ((tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec) / 1000);
	}
	return (0);
}

static void *handle_forks(void *ph)
{
	t_p	*b;

	b = (t_p *)ph;
	while (b->a->p[b->id].right < 0)
	{
		pthread_mutex_lock(&b->a->p[b->r].fork);
		b->a->p[b->id].right = 1;
		if (b->a->p[b->id].left < 0)
		{
			pthread_mutex_unlock(&b->a->p[b->r].fork);
			b->a->p[b->id].right = -1;
			usleep (100);
			continue;
		}
	}
	return(NULL);
}

static void	*routine(void *a)
{	
	t_p	ph;

	ph.a = (t_args *)a;
	ph.id = ph.a->tmp_id;
	ph.a->p[ph.id].left = -1;
	ph.a->p[ph.id].right = -1;
	if (ph.id == ph.a->n - 1)
		ph.r = 0;
	else
		ph.r = ph.id + 1;
	//message(ph.id, ph.r, " ===================forks\n", &ph.a->send_mes);
	ph.a->p[ph.id].last_meal = get_time();
	while (1)
	{
		message(get_time(), ph.id + 1, " is thinking\n", &ph.a->send_mes);
		pthread_create(&ph.a->p[ph.id].second_fork, NULL, &handle_forks, &ph);
		//message(ph.id + 1, ph.r + 1, " =====================================\n", &ph.a->send_mes);
		//message(ph.id + 1, ph.id + 1, " =====================================\n", &ph.a->send_mes);
		while (ph.a->p[ph.id].left < 0)
		{
			pthread_mutex_lock(&ph.a->p[ph.id].fork);
			ph.a->p[ph.id].left = 1;
			if (ph.a->p[ph.id].right < 0)
			{
				pthread_mutex_unlock(&ph.a->p[ph.id].fork);
				pthread_mutex_unlock(&ph.a->p[ph.id].fork);
				ph.a->p[ph.id].left = -1;
				usleep (100);
				continue;
			}
		}
		if (ph.a->p[ph.id].last_meal - get_time() > ph.a->die_time)
		{
			message(get_time(), ph.id + 1, " died\n", &ph.a->send_mes);
			pthread_mutex_unlock(&ph.a->p[ph.id].fork);
			pthread_mutex_unlock(&ph.a->p[ph.r].fork);
			return (NULL);
		}
		ph.a->p[ph.id].last_meal = get_time();
		message(get_time(), ph.id + 1, " has taken a fork\n", &ph.a->send_mes);
		message(get_time(), ph.id + 1, " is eating\n", &ph.a->send_mes);
		usleep(ph.a->eat_time * 1000);
		pthread_mutex_unlock(&ph.a->p[ph.id].fork);
		ph.a->p[ph.id].left = -1;
		pthread_mutex_unlock(&ph.a->p[ph.r].fork);
		ph.a->p[ph.id].right = -1;
		message(get_time(), ph.id + 1, " is sleeping\n", &ph.a->send_mes);
		usleep(ph.a->sleep_time * 1000);
	}
	return (NULL);
}

static int check_args(int argc, char **argv, t_args *a)
{
	if ((argc != 6) && (argc != 5))
		return (ft_putstr_fd("Invalid arguments number. Must be 5 or 4\n", 1));
	a->n = ft_atoi(argv[1]);
	a->die_time = ft_atoi(argv[2]);
	a->eat_time = ft_atoi(argv[3]);
	a->sleep_time = ft_atoi(argv[4]);
	a->number = -1;
	if (argc == 6)
		a->number = ft_atoi(argv[5]);
	if ((a->n < 1) || (a->die_time < 0) || (a->eat_time < 0) || (a->sleep_time < 0) || ( (argc == 6) && (a->number < 0)))
		return (ft_putstr_fd("Invalid arguments.\n", 1));
	return (0);
}

int main (int argc, char *argv[])
{
	t_args	a;
	int		i;
	
	if (check_args(argc, argv, &a) != 0)
		return (1);
	pthread_mutex_init(&a.send_mes, NULL);
	if (!(a.p = malloc(sizeof(t_philo) * a.n)))
		return (ft_putstr_fd("Malloc error\n", 1));
	i = 0;
	while (i < a.n)
		pthread_mutex_init(&a.p[i++].fork, NULL);
	get_time();
	i = -1;
	while (++i < a.n)
	{
		a.tmp_id = i;
		if (pthread_create(&a.p[i].t, NULL, &routine, &a) != 0)
			return (printf("pthread_create error!\n"));
		usleep(1000);
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

