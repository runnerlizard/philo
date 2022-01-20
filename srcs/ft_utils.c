#include "../include/philo.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
    int     j;

	i = 0;
    j = 0;
	while (s[i])
		j = j + write (fd, &s[i++], 1);
    return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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
	int			j;
	char		res;

	j = 0;
	if (n < 0)
	{
		res = '-';
		j = j + write(fd, &res, 1);
	}
	if (n < 0)
		n = - n;
	if (n > 9)
		ft_write_big(fd, n);
	else
	{
		res = n + 48;
		j = j + write(fd, &res, 1);
	}
}
