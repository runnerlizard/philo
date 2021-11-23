#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

pthread_mutex_t	mutex;
int				*i;
int 			j;

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

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
		if (write (fd, &s[i++], 1) == -1)
			return(0);
	return (i);
}

long int	ft_abs(long int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

int	ft_write_small(int fd, long int n)
{
	char	res;

	res = n + 48;
	if (write(fd, &res, 1) == -1)
		return(0);
	return (1);
}

int	ft_write_big(int fd, long int n)
{
	char		res;
	long int	k;
	int			i;

	k = 10;
	while (n / k >= 10)
		k = k * 10;
	i = 0;
	while (k >= 1)
	{
		res = (n % (10 * k)) / k + 48;
		if (write(fd, &res, 1) == -1)
			i++;
		k = k / 10;
	}
	return (i);
}

int	ft_putnbr_fd(int n, int fd)
{
	long int	n1;
	char		res;
	int			i;

	i = 0;
	if (n < 0)
	{
		res = '-';
		if (write(fd, &res, 1) != -1)
			i++;
	}
	n1 = ft_abs(n);
	if (n1 > 9)
		i = i + ft_write_big(fd, n1);
	else
		i = i + ft_write_small(fd, n1);
	return (i);
}

static int check_args(int *i, int argc, char **argv)
{
	int	j;

	if ((argc != 6) && (argc != 5))
		return (printf("Invalid arguments number. Must be 5 or 4\n"));
	j = 0;
	while (argv[++j])
		if ((i[j - 1] = ft_atoi(argv[j])) <= 0)
			return (printf("Invalid argument: %s. Must be positive number\n", argv[j]));
	return (0);
}

void	*routine()
{	
	pthread_mutex_lock(&mutex);
	ft_putnbr_fd(j++, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int main (int argc, char *argv[])
{
	pthread_t		*t;

	if ((i = (int *)malloc(sizeof(int) * argc)) == NULL)
		return (printf("Malloc error.\n"));
	if ((j = check_args(i, argc, argv)) != 0)
		return (printf("%d\n", j));
/*	if ((mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * i[0])) == NULL)
		return (printf("Malloc error for mutex.\n"));*/
	if ((t = (pthread_t *)malloc(sizeof(pthread_t) * i[0])) == NULL)
		return (printf("Malloc error for pthread.\n"));
	pthread_mutex_init(&mutex, NULL);
	j = 0;
	while (j < i[0] - 1)
		if (pthread_create(t + j, NULL, &routine, NULL) != 0)
			return (printf("pthread_create error!\n"));
	while (j-- > 0)
	{
		printf("joined %d\n", j);
		if (pthread_join(t[j], NULL) != 0)
			return (printf("pthread_join error!\n"));
	}
	pthread_mutex_destroy(&mutex);
	while (i[j])
		printf("%d\n", i[j++]);
	return (argc);
}
