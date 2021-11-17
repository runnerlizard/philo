#include "libft.h"

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
