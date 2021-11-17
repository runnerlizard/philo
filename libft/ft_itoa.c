#include "libft.h"

long int	ft_abs(long int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

long int	ft_set_k(long int k, int n)
{
	if ((n > -10) && (n < 10))
		return (1);
	while ((n / k >= 10) || (n / k <= -10))
		k = k * 10;
	return (k);
}

int	ft_set_i(long int k, int i, int n)
{
	if ((n > -10) && (n < 10))
	{
		if (n >= 0)
			return (0);
		else
			return (1);
	}
	while ((n / k >= 10) || (n / k <= -10))
	{
		k = k * 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	k;
	char		*res;

	k = ft_set_k(10, n);
	i = ft_set_i(10, 2, n);
	res = (char *)malloc(sizeof(char) * (i + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
		res[i++] = '-';
	while (k >= 1)
	{
		res[i++] = (ft_abs(n) % (10 * k)) / k + 48;
		k = k / 10;
	}
	res[i] = 0;
	return (res);
}
