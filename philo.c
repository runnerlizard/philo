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
	if ((a > 2147483648) || ((a == 2147483648) & (sign == 1)))
		return (-1);
	return (a * sign);
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

static void	*routine(void *p)
{	
	struct timeval	tv2;
	struct timeval	tv3;
	struct timezone	tz;
	t_philo			ph;

	ph = *(t_philo *)p;
	gettimeofday(&tv3, &tz);
	while (1)
	{
		gettimeofday(&tv2, &tz);
		printf("%ld %d is thinking\n", (tv2.tv_sec - ph->sec) * 1000 + (tv2.tv_usec - ph->usec) / 1000, ph->n);
		pthread_mutex_lock(&mutex);
		gettimeofday(&tv2, &tz);
		if ((tv2.tv_sec - tv3.tv_sec) * 1000 + (tv2.tv_usec - tv3.tv_usec) > i[1] * 1000)
		{
			printf("%ld %d died\n", (tv2.tv_sec - ph->sec) * 1000 + (tv2.tv_usec - ph->usec) / 1000, ph->n);
			pthread_mutex_unlock(&mutex);
			return (NULL);
		}
		printf("%ld %d has taken a fork\n%ld %d is eating\n", (tv2.tv_sec - ph->sec) * 1000 + (tv2.tv_usec - ph->usec) / 1000, ph->n, (tv2.tv_sec - ph->sec) * 1000 + (tv2.tv_usec - ph->usec) / 1000, ph->n);
		tv3.tv_sec = tv2.tv_sec;
		tv3.tv_usec = tv2.tv_usec;
		usleep(i[2] * 1000);
		pthread_mutex_unlock(&mutex);
		gettimeofday(&tv2, &tz);
		printf("%ld %d is sleeping\n", (tv2.tv_sec - ph->sec) * 1000 + (tv2.tv_usec - ph->usec) / 1000, ph->n);
		usleep(i[3] * 1000);
	}
	return (NULL);
}

int main (int argc, char *argv[])
{
	pthread_t		*t;
	t_philo			ph;
	int				i;
	struct timeval	tv1;
	struct timezone	tz;

	if ((i = (int *)malloc(sizeof(int) * argc)) == NULL)
		return (printf("Malloc error.\n"));
	if ((i[argc] = check_args(*ph, argc, argv)) != 0)
		return (1);
/*	if ((mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * i[0])) == NULL)
		return (printf("Malloc error for mutex.\n"));*/
	gettimeofday(&tv1, &tz);
	ph->sec = tv1.tv_sec;
	ph->usec = tv1.tv_usec;
	if ((t = (pthread_t *)malloc(sizeof(pthread_t) * ph->n)) == NULL)
		return (printf("Malloc error for pthread.\n"));
	pthread_mutex_init(&ph->mutex, NULL);
	i = -1;
	while (++i < ph->n)
	{
		if (pthread_create(t + i, NULL, &routine, &ph) != 0)
			return (printf("pthread_create error!\n"));
		usleep(10);
	}
	usleep(200000000);
/*	while (j-- > 0)
	{
		printf("joined %d\n", i[0] - j);
		if (pthread_join(t[j], NULL) != 0)
			return (printf("pthread_join error!\n"));
		usleep(10);
	}*/
	pthread_mutex_destroy(&ph->mutex);
	return (argc);
}
