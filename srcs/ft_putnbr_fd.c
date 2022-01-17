#include "../include/philo.h"

static long int	ft_abs1(long int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

static void	ft_write_small(int fd, long int n)
{
	char	res;
	int		j;

	j = 0;
	res = n + 48;
	j = j + write(fd, &res, 1);
}

static void	ft_write_big(int fd, long int n)
{
	char		res;
	long int	k;
	int			j;

	j = 0;
	k = 10;
	while (n / k >= 10)
		k = k * 10;
	while (k >= 1)
	{
		res = (n % (10 * k)) / k + 48;
		j = j + write(fd, &res, 1);
		k = k / 10;
	}
}

void	ft_putnbr_fd(long int n, int fd)
{
	long int	n1;
	int			j;
	char		res;

	j = 0;
	if (n < 0)
	{
		res = '-';
		j = j + write(fd, &res, 1);
	}
	n1 = ft_abs1(n);
	if (n1 > 9)
		ft_write_big(fd, n1);
	else
		ft_write_small(fd, n1);
}
