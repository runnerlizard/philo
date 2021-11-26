#include "philo.h"

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

static void	*routine(void *ph)
{	
	int		p_num;
	t_philo *local;

	local = (t_philo *)ph;
	p_num = local->p_num + 1;
	local->last_meal[p_num] = get_time();
	while (1)
	{
		message(get_time(), p_num, " is thinking\n", &local->send_mes);
		if (p_num % 2 == 0)
			usleep(local->eat_time / 2);
		pthread_mutex_lock(&local->fork[p_num]);
		if (p_num == local->n)
		{
			//ft_putstr_fd("waiting first\n", 1);
			pthread_mutex_lock(&local->fork[1]);
		}
		else
		{
			//ft_putstr_fd("waiting mine\n", 1);
			pthread_mutex_lock(&local->fork[p_num + 1]);
		}
		usleep(10);
		if (get_time() - local->last_meal[p_num] > local->die_time)
		{
			message(get_time(), p_num, " died\n", &local->send_mes);
			pthread_mutex_unlock(&local->fork[p_num]);
			if (p_num == local->n)
				pthread_mutex_unlock(&local->fork[1]);
			else
				pthread_mutex_unlock(&local->fork[p_num + 1]);
			return (NULL);
		}
		local->last_meal[p_num] = get_time();
		message(get_time(), p_num, " has taken a fork\n", &local->send_mes);
		message(get_time(), p_num, " is eating\n", &local->send_mes);
		usleep(local->eat_time * 1000);
		pthread_mutex_unlock(&local->fork[p_num]);
		if (p_num == local->n)
		{
			//ft_putstr_fd("last philo\n", 1);
			pthread_mutex_unlock(&local->fork[1]);
		}
		else
		{
			//ft_putstr_fd("not last philo\n", 1);
			pthread_mutex_unlock(&local->fork[p_num + 1]);
		}
		message(get_time(), p_num, " is sleeping\n", &local->send_mes);
		usleep(local->sleep_time * 1000);
	}
	return (NULL);
}

static int check_args(t_philo *ph, int argc, char **argv)
{
	if ((argc != 6) && (argc != 5))
		return (printf("Invalid arguments number. Must be 5 or 4\n"));
	ph->n = ft_atoi(argv[1]);
	ph->die_time = ft_atoi(argv[2]);
	ph->eat_time = ft_atoi(argv[3]);
	ph->sleep_time = ft_atoi(argv[4]);
	ph->number = -1;
	if (argc == 6)
		ph->number = ft_atoi(argv[5]);
	if ((ph->n < 1) || (ph->die_time < 0) || (ph->eat_time < 0) || (ph->sleep_time < 0) || ( (argc == 6) && (ph->number < 0)))
		return (printf("Invalid arguments.\n"));
	return (0);
}

int main (int argc, char *argv[])
{
	pthread_t		*t;
	t_philo			*ph;
	int				i;
	
	if (!(ph = malloc(sizeof(t_philo))))
		return (1);
	if (check_args(ph, argc, argv) != 0)
		return (1);
	if (!(ph->fork = (pthread_mutex_t*)malloc(sizeof(*(ph->fork)) * ph->n)))
		return (1);
	ft_putstr_fd("here\n",1);
	if (!(ph->last_meal = (int*)malloc(sizeof(*(ph->last_meal)) * ph->n)))
		return (1);
	ft_putstr_fd("here2\n",1);
	i = 0;
	while (i <= ph->n)
		pthread_mutex_init(&ph->fork[i++], NULL);
	pthread_mutex_init(&ph->send_mes, NULL);
	ft_putnbr_fd(ph->n, 1);
	ft_putstr_fd("here3\n",1);
	if (!(t = (pthread_t *)malloc(sizeof(t) * ph->n)))
		return (printf("Malloc error for pthread.\n"));
	ft_putstr_fd("here4\n",1);
	i = -1;
	get_time();
	while (++i < ph->n)
	{
		ph->p_num = i;
		if (pthread_create(t + i, NULL, &routine, ph) != 0)
			return (printf("pthread_create error!\n"));
		usleep(10);
	}
	usleep(100000000);
/*	while (j-- > 0)
	{
		printf("joined %d\n", i[0] - j);
		if (pthread_join(t[j], NULL) != 0)
			return (printf("pthread_join error!\n"));
		usleep(10);
	}*/

	return (argc);
}
